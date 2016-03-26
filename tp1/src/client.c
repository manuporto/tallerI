#include<stdio.h>
#include<string.h>
#include <stdlib.h>

#include "socket_api.h"
#include "checksum.h"


static void process_file(sktinfo_t *skt, char *filename, int block_size);

static void send_file_info(sktinfo_t *skt, char *new_remote_file, 
        int block_size);

static void send_checksum(sktinfo_t *skt, int checksum);


void cliente(char *hostname, char *port, char *old_local_file, 
        char *new_local_file, char *new_remote_file, int block_size) {
    sktinfo_t skt;

    socket_init(&skt, hostname, port);
    socket_connect(&skt);
    send_file_info(&skt, new_remote_file, block_size);
    process_file(&skt, old_local_file, block_size);
    socket_destroy(&skt);
}

static void send_file_info(sktinfo_t *skt, char *new_remote_file, 
        int block_size) {
    int largo_nombre = strlen(new_remote_file);
    socket_send(skt, &largo_nombre, sizeof(largo_nombre)); 
    socket_send(skt, new_remote_file, largo_nombre);
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
    
    status = 2; //checksum end
    socket_send(skt, &status, sizeof(status));
    fclose(fp);
}

static void send_checksum(sktinfo_t *skt, int checksum) {
    int checksum_inbound = 1;
    socket_send(skt, &checksum_inbound, sizeof(checksum_inbound));
    socket_send(skt, &checksum, sizeof(checksum));
}
