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
#include <vector>

#include "common_socket.h"

#define MAX_MSG_LEN 64

using std::cout;
using std::endl;
using std::vector;

Socket::Socket(addrinfo& res) {
    fd = socket(res.ai_family, res.ai_socktype, res.ai_protocol);
    if (fd == -1) {
        fprintf(stderr, "Error: %s\n", strerror(errno));
    }
}

Socket::Socket(int fd) : fd(fd) {}

void Socket::socket_bind(addrinfo& res) {
    int status = bind(fd, res.ai_addr, res.ai_addrlen);
    if (status == -1) {
        fprintf(stderr, "Error: %s\n", strerror(errno));
    }
}

void Socket::socket_connect(addrinfo& res) {
    int status = connect(fd, res.ai_addr, res.ai_addrlen);
    if (status == -1) {
        fprintf(stderr, "Error: %s\n", strerror(errno));
    }
}

void Socket::socket_listen(int backlog) {
    int status = listen(fd, backlog);
    if (status == -1) {
        fprintf(stderr, "Error: %s\n", strerror(errno));
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

/*void Socket::socket_send(void* buf, int size) {
    return process_message(buf, size, 0);
}

void Socket::socket_receive(void* buf, int size) {
    return process_message(buf, size, 1);
}

void Socket::process_message(void* buf, int size, int mode) {
    char* c_buf = (char*)buf;
    int status;
    int processed = 0;
    bool socket_valid = true;

    while (processed < size) {
        // pos = pos + processed;
        if (mode == 0) {
            status =
                send(fd, &c_buf[processed], size - processed, MSG_NOSIGNAL);
        } else {
            status =
                recv(fd, &c_buf[processed], size - processed, MSG_NOSIGNAL);
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
*/
void Socket::socket_send(string& msg, size_t size) {
    const char* buf = msg.c_str();
    int status;
    size_t processed = 0;
    while (processed < size) {
        // pos = pos + processed;
        status = send(fd, &buf[processed], size - processed, 0);
        if (status <= 0) {
            throw std::runtime_error("Error while attempting to send data.");
        } else {
            // In case of no error status represents the bytes sent/received
            processed += status;
        }
    }
    /*
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
    }*/
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
            // In case of no error status represents the bytes sent/received
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
    /*msg = "";
    int status;
    vector<char> buffer(MAX_MSG_LEN);
    std::vector<char>::iterator nw_data_start = buffer.begin();
    std::vector<char>::iterator nw_data_end = buffer.begin();
    std::vector<char>::iterator it;
    size_t processed = 0;

    while (processed < MAX_MSG_LEN) {
        status = recv(fd, &buffer[processed], MAX_MSG_LEN - processed,
    MSG_NOSIGNAL);
        if (status < 0) {
            throw std::runtime_error("Error while attempting to receive data.");
        } else {
            processed += status;
            it = std::find(buffer.begin(), buffer.end(), '\n');
            if (it != buffer.end()) {
                msg.append(nw_data_start, it);
                break;
            } else {
                std::advance(nw_data_end, processed);
                msg.append(nw_data_start, nw_data_end);
            }
            std::advance(nw_data_start, processed);
        }
    }*/
}

Socket::~Socket() {
    shutdown(fd, SHUT_RDWR);
    close(fd);
}
