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

/*typedef struct sktinfo{
    int fd; // Socket file descriptor
    struct addrinfo *res; // Address info
} sktinfo_t; */

int socket_init(sktinfo_t *self, char *hostname, char *port) {
    int status;
    struct addrinfo hints;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    if (!hostname) {
        hints.ai_flags = AI_PASSIVE;
    }

    status = getaddrinfo(hostname, port, &hints, &self->res);
    if (status != 0) {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
        return 1;      
    }
    
    self->fd = socket(self->res->ai_family, self->res->ai_socktype, 
            self->res->ai_protocol); 
    if (self->fd == -1) {
        printf("Error: %s\n", strerror(errno));
        freeaddrinfo(self->res);
        return 1;
    }

    return 0;
}

int socket_bind(sktinfo_t *self) {
    int status = bind(self->fd, self->res->ai_addr, self->res->ai_addrlen);
    if (status == -1) {
        printf("Error: %s\n", strerror(errno));
        close(self->fd);
        freeaddrinfo(self->res);
        return 1;
    }

    freeaddrinfo(self->res);
    return 0;
}

int socket_connect(sktinfo_t *self) {
    int status = connect(self->fd, self->res->ai_addr, self->res->ai_addrlen);
    if (status == -1) {
        printf("Error: %s\n", strerror(errno));
        close(self->fd);
        freeaddrinfo(self->res);
        return 1;
    }
    
    freeaddrinfo(self->res);
    return 0;
}

int socket_listen(sktinfo_t *self, int backlog) {
    int status = listen(self->fd, backlog);
    if (status == -1) {
        printf("Error: %s\n", strerror(errno));
        close(self->fd);
        return 1;
    }

    return 0;
}

int socket_accept(sktinfo_t *self) {
    int tempskt = accept(self->fd, NULL, NULL);
    
    if (tempskt == -1) {
        printf("Error: %s\n", strerror(errno));
        close(self->fd);
        return 1;
    }
    dup2(tempskt, self->fd); 
    close(self->fd);
    self->fd = tempskt;
    return 0;
}

int socket_send(sktinfo_t *self, char *msg, int len) {
    send(self->fd, msg, len, 0);
    return 0;
}

int socket_receive(sktinfo_t *self, char *buf, int len) {
    recv(self->fd, buf, len, 0);
    return 0;
}

void socket_destroy(sktinfo_t *self) {
    shutdown(self->fd, SHUT_RDWR);
    close(self->fd);
}
