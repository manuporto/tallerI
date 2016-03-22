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

    char client_reply[256];
    socket_receive(&skt, client_reply, 256);
    puts(client_reply);
    socket_destroy(&skt);
}
