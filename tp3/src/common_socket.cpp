#include <algorithm>
#include <cerrno>
#include <cstdio>
#include <stdexcept>
#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <unistd.h>

#include "common_socket.h"

#define MAX_MSG_LEN 1024

using std::string;

Socket::Socket(addrinfo& res) {
    fd = socket(res.ai_family, res.ai_socktype, res.ai_protocol);
    if (fd == -1) {
        fprintf(stderr, "Error: %s\n", strerror(errno));
        throw std::runtime_error(
            "Error while attempting to create a new file descriptor.");
    }
}

Socket::Socket(int fd) : fd(fd) {}

void Socket::socket_bind(addrinfo& res) {
    int status = bind(fd, res.ai_addr, res.ai_addrlen);
    if (status == -1) {
        fprintf(stderr, "Error: %s\n", strerror(errno));
        throw std::runtime_error("Error while attempting to bind.");
    }
}

void Socket::socket_connect(addrinfo& res) {
    int status = connect(fd, res.ai_addr, res.ai_addrlen);
    if (status == -1) {
        fprintf(stderr, "Error: %s\n", strerror(errno));
        throw std::runtime_error("Error while attempting to connect.");
    }
}

void Socket::socket_listen(int backlog) {
    int status = listen(fd, backlog);
    if (status == -1) {
        fprintf(stderr, "Error: %s\n", strerror(errno));
        throw std::runtime_error(
            "Error while attempting to listen for connections.");
    }
}

Socket* Socket::socket_accept() {
    int tempskt = accept(fd, NULL, NULL);
    if (tempskt == -1) {
        throw std::runtime_error(
            "Error while attempting to accept a new connection.");
    }
    return new Socket(tempskt);
}

void Socket::socket_send(string& msg, size_t size) {
    const char* buf = msg.c_str();
    int status;
    size_t processed = 0;
    while (processed < size) {
        status = send(fd, &buf[processed], size - processed, 0);
        if (status <= 0) {
            throw std::runtime_error("Error while attempting to send data.");
        } else {
            processed += status;
        }
    }
}

void Socket::socket_receive(string& msg) {
    size_t size = MAX_MSG_LEN;
    size_t pos;
    size_t processed = 0;
    char buf[MAX_MSG_LEN];
    memset(buf, '\0', MAX_MSG_LEN);
    int status = 0;
    string partial_msg;
    while (processed < size) {
        status = recv(fd, &buf[processed], size - processed, 0);
        if (status <= 0) {
            throw std::runtime_error("Error while attempting to receive data.");
        } else {
            processed += status;
            partial_msg = string(buf, MAX_MSG_LEN);
            pos = partial_msg.find_last_of('\n');
            if (pos != string::npos) {
                msg = partial_msg.substr(0, pos);
                msg += "\n";
                break;
            }
        }
    }
}

Socket::~Socket() {
    shutdown(fd, SHUT_RDWR);
    close(fd);
}
