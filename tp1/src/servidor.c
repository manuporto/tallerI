#include<stdio.h>
#include<string.h>

#include "socket_api.h"

void servidor(char *port) {
    sktinfo_t skt;

    socket_init(&skt, NULL, port);

    socket_bind(&skt);
    socket_listen(&skt, 10);
    
    // accept incoming connections
    socket_accept(&skt); 

    char msg[] = "Connection made";
    int len;

    len = strlen(msg);
    socket_send(&skt, msg, len);

    int client_reply;
    socket_receive(&skt, &client_reply, sizeof(client_reply));
    char old_client_file[client_reply];
    socket_receive(&skt, old_client_file, client_reply);
    int block_size;
    socket_receive(&skt, &block_size, sizeof(block_size));
    printf("%d\n%s\n%d\n", client_reply, old_client_file, block_size);
    socket_destroy(&skt);
}
