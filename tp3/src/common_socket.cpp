#include <cerrno>
#include <cstdio>
#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <unistd.h>
#include <vector>

#include "common_socket.h"

using std::cout;
using std::endl;
using std::vector;

Socket::Socket(addrinfo& res)
{
    fd = socket(res.ai_family, res.ai_socktype, res.ai_protocol);
    if (fd == -1) {
        fprintf(stderr, "Error: %s\n", strerror(errno));
    }
}

Socket::Socket(int fd) : fd(fd)
{
}

void Socket::socket_bind(addrinfo& res)
{
    int status = bind(fd, res.ai_addr, res.ai_addrlen);
    if (status == -1) {
        fprintf(stderr, "Error: %s\n", strerror(errno));
    }
}

void Socket::socket_connect(addrinfo& res)
{
    int status = connect(fd, res.ai_addr, res.ai_addrlen);
    if (status == -1) {
        fprintf(stderr, "Error: %s\n", strerror(errno));
    }
}

void Socket::socket_listen(int backlog)
{
    int status = listen(fd, backlog);
    if (status == -1) {
        fprintf(stderr, "Error: %s\n", strerror(errno));
    }
}

Socket* Socket::socket_accept()
{
    int tempskt = accept(fd, NULL, NULL);
    if (tempskt == -1) {
        fprintf(stderr, "Error: %s\n", strerror(errno));
    }
    return new Socket(tempskt);
}

void Socket::socket_send(void* buf, int size)
{
    return process_message(buf, size, 0);
}

void Socket::socket_receive(void* buf, int size)
{
    return process_message(buf, size, 1);
}

void Socket::process_message(void* buf, int size, int mode)
{
    char* c_buf = (char*)buf;
    int status;
    int processed = 0;
    bool socket_valid = true;

    while (processed < size) {
        // pos = pos + processed;
        if (mode == 0) {
            status = send(fd, &c_buf[processed], size - processed, MSG_NOSIGNAL);
        } else {
            status = recv(fd, &c_buf[processed], size - processed, MSG_NOSIGNAL);
        }

        if (status <= 0) {
            socket_valid = false;
        } else {
            // In case of no error status represents the bytes sent/received
            processed += status;
        }
    }

    if (!socket_valid) {
        cout << "Error" << endl;
    }
}

void Socket::socket_send(string& msg, size_t size)
{
    int status;
    vector<char> buffer(msg.begin(), msg.end());
    size_t processed = 0;
    bool socket_valid = true;
    while (processed < size) {
        status = send(fd, &buffer[processed], size - processed, MSG_NOSIGNAL);
        if (status <= 0) {
            socket_valid = false;
        } else {
            processed += status;
        }
    }

    if (!socket_valid) {
        cout << "Error" << endl;
    }
}

void Socket::socket_receive(string& msg, size_t size)
{
    msg = "";
    int status;
    vector<char> buffer(size);
    std::vector<char>::iterator nw_data_start = buffer.begin();
    std::vector<char>::iterator nw_data_end = buffer.begin();
    size_t processed = 0;
    bool socket_valid = true;

    while (processed < size) {
        status = recv(fd, &buffer[processed], size - processed, MSG_NOSIGNAL);
        if (status <= 0) {
            socket_valid = false;
        } else {
            processed += status;
            std::advance(nw_data_end, processed);
            msg.append(nw_data_start, nw_data_end);
            std::advance(nw_data_start, processed);
        }
    }

    if (!socket_valid) {
        cout << "Error" << endl;
    }
}

Socket::~Socket()
{
    shutdown(fd, SHUT_RDWR);
    close(fd);
}