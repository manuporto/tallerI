#include<limits.h>
#include<stdio.h>
#include<string.h>

#include "socket_api.h"
#include "dynamic_array.h"

static void receive_file_info(sktinfo_t *skt, char *filename, 
        int filename_length, int *block_size);

static void receive_file_data(sktinfo_t *skt, array_t *chksm_array);

static int compare_files(sktinfo_t *skt, char *filename, array_t *chksm_array,
        int block_size);

void servidor(char *port) {
    sktinfo_t skt;

    socket_init(&skt, NULL, port);

    socket_bind(&skt);
    socket_listen(&skt, 10);
    
    // accept incoming connections
    socket_accept(&skt); 
    

    int filename_length;
    socket_receive(&skt, &filename_length, sizeof(filename_length));   

    char filename[filename_length];
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
    //printf("%s\n", server_file);
    socket_receive(skt, block_size, sizeof(*block_size));
    //printf("%d\n", block_size);
}

static void receive_file_data(sktinfo_t *skt, array_t *chksm_array) {
    int checksum, operation;
   
    socket_receive(skt, &operation, sizeof(operation));
    while (operation == 1) {
        socket_receive(skt, &checksum, sizeof(checksum));
        array_append(chksm_array, checksum);
        socket_receive(skt, &operation, sizeof(operation));
    }
}
static int compare_files(sktinfo_t *skt, char *filename, array_t *chksm_array,
        int block_size) {
    int a = 0;
    for(int i = 0; i < chksm_array->elements; i++) {
        a = chksm_array->data[i];
        printf("check: %x\n", a);
    }

    return a;
}
