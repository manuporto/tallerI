#include<limits.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "checksum.h"
#include "dynamic_array.h"
#include "protocol.h"
#include "socket_api.h"

// Sets filename and block_size
static void receive_file_info(sktinfo_t *skt, char *filename, 
        int filename_length, int *block_size);

// Receives a checksum array and initializes it with the info of sent by the
// client
static void receive_file_data(sktinfo_t *skt, array_t *chksm_array);

// Calculates the checksums of the server local files and compares them with
// the ones in the checksum array
static int compare_files(sktinfo_t *skt, char *filename, array_t *chksm_array,
        int block_size);

// Sends the index of the checksum of the common bytes between client and
// server
static void send_info_common_bytes(sktinfo_t *skt, int index);

static void send_diff_bytes(sktinfo_t *skt, FILE *fp, long start_diff, 
        long end_diff, long actual_position);
 

void servidor(char *port) {
    sktinfo_t skt;

    socket_init(&skt, NULL, port);

    socket_bind(&skt);
    socket_listen(&skt, 10);
    
    // accept incoming connections
    socket_accept(&skt); 
    

    int filename_length;
    socket_receive(&skt, &filename_length, sizeof(filename_length));   

    int kFileL = filename_length;
    char filename[kFileL];
    int block_size;
    receive_file_info(&skt, filename, filename_length, &block_size);
    array_t chksm_array;
    array_init(&chksm_array, 10);
    receive_file_data(&skt, &chksm_array);
    compare_files(&skt, filename, &chksm_array, block_size);
    array_destroy(&chksm_array);
    socket_destroy(&skt);
}

static void receive_file_info(sktinfo_t *skt, char *filename, 
        int filename_length, int *block_size) {
    //printf("%d\n", filename_length);
    socket_receive(skt, filename, filename_length);
    //printf("%s\n", filename);
    socket_receive(skt, block_size, sizeof(*block_size));
    //printf("%d\n", *block_size);
}

static void receive_file_data(sktinfo_t *skt, array_t *chksm_array) {
    int checksum, operation;
   
    socket_receive(skt, &operation, sizeof(operation));
    while (operation == CHKSM_IN) {
        socket_receive(skt, &checksum, sizeof(checksum));
        array_append(chksm_array, checksum);
        socket_receive(skt, &operation, sizeof(operation));
    }
}

static int compare_files(sktinfo_t *skt, char *filename, array_t *chksm_array,
        int block_size) {
    FILE *fp = fopen(filename, "r");
    long actual_pos = ftell(fp);
    long start_diff = actual_pos;
    long end_diff = actual_pos;
     
    int server_chksm = 0;
    int client_chksm_pos = -1;
    int status  = 2;
    int s;
    while (!feof(fp)) {
        switch (status) {
            case 0:
                end_diff = actual_pos - (long) block_size + 1; 
                fseek(fp, end_diff, SEEK_SET);
                break;
            case 1:
                send_diff_bytes(skt, fp, start_diff, end_diff, actual_pos);
                send_info_common_bytes(skt, client_chksm_pos);
                start_diff = actual_pos;
                end_diff = actual_pos;
                break;
        }
        server_chksm = process_block(fp, block_size);
        actual_pos = ftell(fp);
        if (server_chksm >= 0) {
            client_chksm_pos = array_find(chksm_array, server_chksm);
        }

        if (client_chksm_pos == -1) {
            status = 0;
        } else {
            status = 1;
        }
    }
    send_diff_bytes(skt, fp, start_diff, actual_pos, actual_pos);
    s = END_OF_FILE;
    socket_send(skt, &s, sizeof(s));
    fclose(fp);
    return 0;
}

static void send_info_common_bytes(sktinfo_t *skt, int index) {
    int status = NB_IN;
    socket_send(skt, &status, sizeof(status)); 
    socket_send(skt, &index, sizeof(index));
}

static void send_diff_bytes(sktinfo_t *skt, FILE *fp, long start_diff, 
        long end_diff, long actual_position) {
    int kBufSize = (int) end_diff - start_diff;
    if (kBufSize == 0) {
        return;
    }
    int status = BYTE_IN;
    socket_send(skt, &status, sizeof(status));
    socket_send(skt, &kBufSize, sizeof(kBufSize));
    int kBuf = kBufSize;
    char buf[kBuf];
    int i = 0;
    fseek(fp, start_diff, SEEK_SET);
    while (ftell(fp) <= end_diff && !feof(fp)) {
       buf[i] = fgetc(fp); 
       i++;
    }

    socket_send(skt, buf, kBufSize);
    fseek(fp, actual_position, SEEK_SET);
}
