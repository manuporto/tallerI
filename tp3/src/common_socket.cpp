#include <cerrno>
#include <cstdio>
#include <iostream>
#include <string>
#include <cstring>
#include <sys/common_socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <unistd.h>

#include "common_socket.h"

Socket::Socket(addrinfo& res) {
    fd = socket(res.ai_family, res.ai_socktype, res.ai_protocol);
    if(fd == -1) {
	fprintf(stderr, "Error: %s\n", strerror(errno));
    }
}

Socket::Socket(int fd) : fd(fd) {}

void Socket::socket_bind(addrinfo& res) {
    int status = bind(fd, res.ai_addr, res.ai_addrlen);
    if(status == -1) {
	fprintf(stderr, "Error: %s\n", strerror(errno));
    }
}

void Socket::socket_connect(addrinfo& res) {
    int status = connect(fd, res.ai_addr, res.ai_addrlen);
    if(status == -1) {
	fprintf(stderr, "Error: %s\n", strerror(errno));
    }
}

void Socket::socket_listen(int backlog) {
    int status = listen(fd, backlog);
    if(status == -1) {
	fprintf(stderr, "Error: %s\n", strerror(errno));
    }
}

Socket Socket::socket_accept() {
    int tempskt = accept(fd, NULL, NULL);
    return Socket(tempskt);
}

void Socket::socket_send(void* buf, int size) {
    return process_message(buf, size, 0);
}

void Socket::socket_receive(void* buf, int size) {
    return process_message(buf, size, 1);
}

void Socket::process_message(void* buf, int size, int mode) {
    int status;
    char* c_buf = (char*)buf;
    int processed = 0;
    bool socket_valid = true;

    while(processed < size) {
	// pos = pos + processed;
	if(mode == 0) {
	    status = send(fd, &c_buf[processed], size - processed, 0);
	} else {
	    status = recv(fd, &c_buf[processed], size - processed, 0);
	}

	if(status <= 0) {
	    socket_valid = false;
	} else {
	    // In case of no error status represents the bytes sent/received
	    processed += status;
	}
    }

    if(socket_valid) {
	throw "Error";
    }
}

Socket::~Socket() {
    shutdown(fd, SHUT_RDWR);
    close(fd);
}