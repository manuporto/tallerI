#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 1
#endif

#include<errno.h>
#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netdb.h>
#include<unistd.h>

#include "socket_api.h"

class Socket {
    private:
        int fd;

     static int process_message(int skt_fd, void *buf, int size, int mode) {
        int status;
        char *c_buf = (char *) buf;
        int processed = 0;
        bool socket_valid = true;

        while (processed < size) {
            //pos = pos + processed;
            if (mode == 0){
                status = send(skt_fd, &c_buf[processed], size - processed, 0); 
            } else {
                status = recv(skt_fd, &c_buf[processed], size - processed, 0);
            }

            if (status <= 0) {
                socket_valid = false;
            } else {
                // In case of no error status represents the bytes sent/received
                processed += status;
            }
        }

        if (socket_valid) {
            return processed;
        } else {
            return -1;
        }
    }

    Socket(sktinfo_t *self, char *hostname, char *port) {
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
            return -1;      
        }
        
        self->fd = socket(self->res->ai_family, self->res->ai_socktype, 
                self->res->ai_protocol); 
        if (self->fd == -1) {
            fprintf(stderr, "Error: %s\n", strerror(errno));
            freeaddrinfo(self->res);
            return -1;
        }

        return 0;
    }

    int socket_bind(sktinfo_t *self) {
        int status = bind(self->fd, self->res->ai_addr, self->res->ai_addrlen);
        if (status == -1) {
            fprintf(stderr, "Error: %s\n", strerror(errno));
            close(self->fd);
            freeaddrinfo(self->res);
            return -1;
        }

        return 0;
    }

    int socket_connect(sktinfo_t *self) {
        int status = connect(self->fd, self->res->ai_addr, self->res->ai_addrlen);
        if (status == -1) {
            fprintf(stderr, "Error: %s\n", strerror(errno));
            close(self->fd);
            freeaddrinfo(self->res);
            return -1;
        }
        
        return 0;
    }

    int socket_listen(sktinfo_t *self, int backlog) {
        int status = listen(self->fd, backlog);
        if (status == -1) {
            fprintf(stderr, "Error: %s\n", strerror(errno));
            close(self->fd);
            return -1;
        }

        return 0;
    }

    int socket_accept(sktinfo_t *self) {
        int tempskt = accept(self->fd, NULL, NULL);
        
        if (tempskt == -1) {
            fprintf(stderr, "Error: %s\n", strerror(errno));
            close(self->fd);
            return -1;
        }
        dup2(tempskt, self->fd); 
        close(self->fd);
        self->fd = tempskt;
        return 0;
    }

    int socket_send(sktinfo_t *self, void *buf, int size) {
        return process_message(self->fd, buf, size, 0);
    }

    int socket_receive(sktinfo_t *self, void *buf, int size) {
        return process_message(self->fd, buf, size, 1);
    }

    ~Socket(sktinfo_t *self) {
        freeaddrinfo(self->res);
        shutdown(self->fd, SHUT_RDWR);
        close(self->fd);
    }   
};

