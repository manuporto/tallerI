#include "server_server.h"

Server::Server(string port) {
    addrinfo hints;
    memset(&hints, 0, sizeof(addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    getaddrinfo(NULL, port.c_str(), &hints, &res);
    *skt = Socket(*res);
    skt->socket_bind(*res);
    skt->socket_listen(10);
}

Server::~Server() {}
