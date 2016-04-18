#include <errno>
#include <iostream>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <unistd.h>

#include "socket2.h"

socket2::socket2(addrinfo& res) {
    fd = socket(res.ai_family, res.ai_socktype, res.ai_protocol);
    if(self->fd == -1) {
	fprintf(stderr, "Error: %s\n", strerror(errno));
    }
}

socket2::socket2(int fd) : fd(fd) {
}

void socket2::socket_bind(addrinfo& res) {
    int status = bind(fd, res.ai_addr, res.ai_addrlen);
    if(status == -1) {
	fprintf(stderr, "Error: %s\n", strerror(errno));
    }
}

void socket2::socket_connect(addrinfo& res) {
    int status = connect(fd, res.ai_addr, res.ai_addrlen);
    if(status == -1) {
	fprintf(stderr, "Error: %s\n", strerror(errno));
    }
}

void socket2::socket_listen(int backlog) {
    int status = listen(fd, backlog);
    if(status == -1) {
	fprintf(stderr, "Error: %s\n", strerror(errno));
    }
}

socket2* socket2::socket_accept() {
    int tempskt = accept(fd, NULL, NULL);
    return new socket2(tempskt);
}

void socket2::socket_send(void* buf, int size) {
    return process_message(buf, size, 0);
}

void socket2::socket_receive(void* buf, int size) {
    return process_message(buf, size, 1);
}

void socket2::process_message(void* buf, int size, int mode) {
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

socket2::~socket2() {
    shutdown(fd, SHUT_RDWR);
    close(fd);
}