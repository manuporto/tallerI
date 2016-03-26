#include<limits.h>
#include<stdio.h>
#include<string.h>

#include "socket_api.h"
#include "dynamic_array.h"

static void receive_file_info(sktinfo_t *skt);

static void receive_file_data(sktinfo_t *skt, array_t *chksm_array);


void servidor(char *port) {
    sktinfo_t skt;

    socket_init(&skt, NULL, port);

    socket_bind(&skt);
    socket_listen(&skt, 10);
    
    // accept incoming connections
    socket_accept(&skt); 

    receive_file_info(&skt);

    array_t chksm_array;
    array_init(&chksm_array, 10);
    receive_file_data(&skt, &chksm_array);
    array_destroy(&chksm_array);
    socket_destroy(&skt);
}

static void receive_file_info(sktinfo_t *skt) {
    int filename_length;
    socket_receive(skt, &filename_length, sizeof(filename_length));
    //printf("%d\n", filename_length);
    char server_file[filename_length + 1];
    socket_receive(skt, server_file, filename_length);
    //printf("%s\n", server_file);
    int block_size;
    socket_receive(skt, &block_size, sizeof(block_size));
    //printf("%d\n", block_size);
}

static void receive_file_data(sktinfo_t *skt, array_t *chksm_array) {
    int checksum, operation;
   
    socket_receive(skt, &operation, sizeof(operation));
    while (operation == 1) {
        socket_receive(skt, &checksum, sizeof(checksum));
        printf("%x\n", checksum);
        socket_receive(skt, &operation, sizeof(operation));
    }
}

