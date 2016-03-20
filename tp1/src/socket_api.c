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

int socket_init(int *self, char *hostname, char *port, struct addrinfo *res) {
    int status;
    struct addrinfo hints;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    if (strcmp(hostname,"") == 0) {
        hints.ai_flags = AI_PASSIVE;
        status = getaddrinfo(NULL, port, &hints, &res);
    } else {
        status = getaddrinfo(hostname, port, &hints, &res);
    }

    if (status != 0) {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
        return 1;      
    }
    
    *self = socket(res->ai_family, res->ai_socktype, res->ai_protocol); 
    if (*self == -1) {
        printf("Error: %s\n", strerror(errno));
        freeaddrinfo(res);
        return 1;
    }

    return 0;
};

int socket_bind(int *self, struct addrinfo *res) {
    int status = bind(*self, res->ai_addr, res->ai_addrlen);
    if (status == -1) {
        printf("Error: %s\n", strerror(errno));
        close(*self);
        freeaddrinfo(res);
        return 1;
    }

    freeaddrinfo(res);
    return 0;
}

int socket_connect(int *self, struct addrinfo *res) {
    int status = connect(*self, res->ai_addr, res->ai_addrlen);
    if (status == -1) {
        printf("Error: %s\n", strerror(errno));
        close(*self);
        freeaddrinfo(res);
        return 1;
    }
    
    freeaddrinfo(res);
    return 0;
}

int socket_listen(int *self, int backlog) {
    int status = listen(*self, backlog);
    if (status == -1) {
        printf("Error: %s\n", strerror(errno));
        close(*self);
        return 1;
    }

    return 0;
}

int socket_accept(int *self, int *peerskt) {
    *peerskt = accept(*self, NULL, NULL);
    if (*peerskt == -1) {
        printf("Error: %s\n", strerror(errno));
        close(*self);
        return 1;
    }

    return 0;
}

int socket_send(int *self, char *msg, int size);

int socket_receive(int *self, char *buf, int size);

void socket_destroy(int *self) {
    shutdown(*self, SHUT_RDWR);
    close(*self);
}
