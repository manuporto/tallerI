#include <errno>
#include <iostream>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <unistd.h>

#include "socket2.h"

socket2::socket2(string hostname, string port, addrinfo& res) {
    int status;
    addrinfo hints;

    memset(&hints, 0, sizeof(addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    if (!hostname) {
        hints.ai_flags = AI_PASSIVE;
    }

    status = getaddrinfo(hostname.c_str(), port.c_str(), &hints, res);
    if (status != 0) {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
    }

    fd = socket(res.ai_family, res.ai_socktype, res.ai_protocol);
    if (self->fd == -1) {
        fprintf(stderr, "Error: %s\n", strerror(errno));
    }
}

void socket2::socket_bind(addrinfo& res) {
    int status = bind(fd, res.ai_addr, res.ai_addrlen);
    if (status == -1) {
        fprintf(stderr, "Error: %s\n", strerror(errno));
    }
}

void socket2::socket_connect(addrinfo& res) {
    int status = connect(fd, res.ai_addr, res.ai_addrlen);
    if (status == -1) {
        fprintf(stderr, "Error: %s\n", strerror(errno));
    }
}

void socket2::socket_listen(int backlog) {
    int status = listen(fd, backlog);
    if (status == -1) {
        fprintf(stderr, "Error: %s\n", strerror(errno));
    }
}

void socket2::socket_accept() {}

void socket2::socket_send(void* buf, int size) {}

void socket2::socket_receive(void* buf, int size) {}

void socket2::process_message(void* buf, int size, int mode) {}

socket2::~socket2() {
    shutdown(fd, SHUT_RDWR);
    close(fd);
}