#include<stdio.h>
#include<string.h>
#include <stdlib.h>

#include "socket_api.h"
#include "checksum.h"


void cliente(char *hostname, char *port, char *old_local_file, 
        char *new_local_file, char *new_remote_file, int block_size) {
    sktinfo_t skt;

    socket_init(&skt, hostname, port);
    socket_connect(&skt);
    int largo_nombre = strlen(old_local_file);
    socket_send(&skt, &largo_nombre, sizeof(largo_nombre)); 
    socket_send(&skt, old_local_file, largo_nombre);
    socket_send(&skt, &block_size, sizeof(block_size));

    leer_archivo(old_local_file, block_size);
    socket_destroy(&skt);
}
