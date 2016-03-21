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

    socket_init(&skt, "", "8080");

    socket_bind(&skt);
    socket_listen(&skt, 10);
    
    // accept incoming connections
    sktinfo_t peerskt;
    socket_accept(&skt, &peerskt); 

    char msg[] = "Connection made";
    int len, bytes_send;

    len = strlen(msg);
    bytes_send = send(peerskt.fd, msg, len, 0);

    socket_destroy(&skt);
    socket_destroy(&peerskt);
}
