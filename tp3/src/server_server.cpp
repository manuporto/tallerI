#include <iostream>
#include <cstring>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#include "common_socket.h"
#include "server_receiver.h"
#include "server_server.h"

using std::string;
using std::cin;
using std::cout;
using std::endl;

Server::Server(string port) {
    addrinfo hints;
    memset(&hints, 0, sizeof(addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    getaddrinfo(NULL, port.c_str(), &hints, &res);
    sv_skt = new Socket(*res);
    sv_skt->socket_bind(*res);
    sv_skt->socket_listen(10);
    string cmd;
    getline(cin, cmd);
    get_data();
}

void Server::get_data() {
    Socket* c_skt = sv_skt->socket_accept();
    Receiver rcivr(c_skt, tmpts);
    rcivr.start();
    rcivr.join();
}

Server::~Server() {}
