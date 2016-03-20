#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 1
#endif

#include<errno.h>
#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netdb.h>
//#include<netinet/in.h>
#include<unistd.h>

int main() {
    int status, skt, peerskt;
    struct addrinfo hints;
    struct addrinfo *res;
    struct sockaddr_storage their_addr;
    socklen_t addr_size;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    status = getaddrinfo(NULL, "8080", &hints, &res);

    if (status != 0) {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
        return 1;
    }

    skt = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    bind(skt, res->ai_addr, res->ai_addrlen);
    freeaddrinfo(res);
    listen(skt, 10);
    
    // accept incoming connections
    addr_size = sizeof(struct sockaddr_storage);
    peerskt = accept(skt, (struct sockaddr *)&their_addr, &addr_size); 

    char msg[] = "Connection made";
    int len, bytes_send;

    len = strlen(msg);
    bytes_send = send(peerskt, msg, len, 0);

    shutdown(peerskt, SHUT_RDWR);
    close(peerskt);
    shutdown(skt, SHUT_RDWR);
    close(skt);
}
