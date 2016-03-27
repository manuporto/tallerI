#include<stdio.h>
#include<string.h>
#include <stdlib.h>

#include "socket_api.h"
#include "checksum.h"
#include "protocol.h"


static void process_file(sktinfo_t *skt, char *filename, int block_size);

static void send_file_info(sktinfo_t *skt, char *new_remote_file, 
        int block_size);

static void send_checksum(sktinfo_t *skt, int checksum);

// Receives new bytes and index of the bytes that both files share.
static void receive_new_file(sktinfo_t *skt, char *new_local_file, 
        char *old_local_file, int block_size);

static void write_old_bytes(sktinfo_t *skt, FILE *new_fp, FILE *old_fp, 
        int block_size);


void cliente(char *hostname, char *port, char *old_local_file, 
        char *new_local_file, char *new_remote_file, int block_size) {
    sktinfo_t skt;
    socket_init(&skt, hostname, port);
    socket_connect(&skt);
    send_file_info(&skt, new_remote_file, block_size);
    process_file(&skt, old_local_file, block_size);
    receive_new_file(&skt, new_local_file, old_local_file, block_size);
    socket_destroy(&skt);
}

static void send_file_info(sktinfo_t *skt, char *new_remote_file, 
        int block_size) {
    int filename_length = strlen(new_remote_file) + 1;
    socket_send(skt, &filename_length, sizeof(filename_length)); 
    socket_send(skt, new_remote_file, filename_length);
    socket_send(skt, &block_size, sizeof(block_size));
}

static void process_file(sktinfo_t *skt, char *filename, int block_size) {
    FILE *fp = fopen(filename, "r");
    int checksum, status;
    while (!feof(fp)) {
        checksum = process_block(fp, block_size);
        if (checksum >= 0) {
            send_checksum(skt, checksum);
        }
    }
    
    status = CHKSM_END; 
    socket_send(skt, &status, sizeof(status));
    fclose(fp);
}

static void send_checksum(sktinfo_t *skt, int checksum) {
    int s = CHKSM_IN;
    socket_send(skt, &s, sizeof(s));
    socket_send(skt, &checksum, sizeof(checksum));
}

static void receive_new_file(sktinfo_t *skt, char *new_local_file, 
        char *old_local_file, int block_size) {
    FILE *old_fp = fopen(old_local_file, "r");
    FILE *new_fp = fopen(new_local_file, "w");
    int status, kBufSize;
    socket_receive(skt, &status, sizeof(status));

    while (status != END_OF_FILE) {
        switch (status) {
            case NB_IN:
                write_old_bytes(skt, new_fp, old_fp, block_size);
                
                break;
            case BYTE_IN:
                socket_receive(skt, &kBufSize, sizeof(kBufSize));
                char buf[kBufSize];
                socket_receive(skt, buf, kBufSize);
                fwrite(buf, sizeof(char), kBufSize, new_fp);
                printf("RECV File chunk %d bytes\n", kBufSize);
                break;
        }

        socket_receive(skt, &status, sizeof(status));
    }

    printf("RECV End of file\n");
    fclose(old_fp);
    fclose(new_fp);
}

static void write_old_bytes(sktinfo_t *skt, FILE *new_fp, FILE *old_fp, 
        int block_size) {
    int block_index;
    char c;
    socket_receive(skt, &block_index, sizeof(block_index)); 
    fseek(old_fp, (long) block_index * block_size, SEEK_SET);

    for (int i = 0; i < block_size && !feof(old_fp); i++) {
        c = fgetc(old_fp);        
        fwrite(&c, sizeof(c), sizeof(c), new_fp);
    }

    rewind(old_fp);
    printf("RECV Block index %d\n", block_index);
}
