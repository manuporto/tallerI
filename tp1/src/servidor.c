#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 1
#endif

#include<errno.h>
#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netdb.h>
#include<unistd.h>


#include "socket_api.h"

int main() {
    sktinfo_t skt;

    socket_init(&skt, NULL, "8080");

    socket_bind(&skt);
    socket_listen(&skt, 10);
    
    // accept incoming connections
    sktinfo_t peerskt;
    socket_accept(&skt, &peerskt); 

    char msg[] = "Connection made";
    int len;

    len = strlen(msg);
    socket_send(&peerskt, msg, len);

    char client_reply[256];
    socket_receive(&peerskt, client_reply, 256);
    puts(client_reply);
    socket_destroy(&skt);
    socket_destroy(&peerskt);
}
