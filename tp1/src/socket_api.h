#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 1
#endif

#ifndef SOCKET_API_H_
#define SOCKET_API_H_

#include<errno.h>
#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netdb.h>
#include<unistd.h>

typedef struct sktinfo {
    int fd; // Socket file descriptor
    struct addrinfo *res; // Address info
} sktinfo_t;

void socket_destroy(sktinfo_t *self);
int socket_receive(sktinfo_t *self, void *buf,int size);
int socket_send(sktinfo_t *self, void *msg,int size);
int socket_accept(sktinfo_t *self);
int socket_listen(sktinfo_t *self, int backlog);
int socket_connect(sktinfo_t *self);
int socket_bind(sktinfo_t *self);
int socket_init(sktinfo_t *self, char *hostname, char *port);

#endif
