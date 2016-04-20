#include <iostream>
#include <cstring>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#include "common_socket.h"
#include "server_server.h"

using std::string;
using std::cout;

Server::Server(string port) {    
    addrinfo hints;
    memset(&hints, 0, sizeof(addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    getaddrinfo(NULL, port.c_str(), &hints, &res);
    cout << "check";
    *skt = Socket(*res);
    /*
    skt->socket_bind(*res);
    skt->socket_listen(10);
    cout << "check";
    Socket c_skt = skt->socket_accept();
    cout << "check";
    */
    // string msg;
    // c_skt.socket_receive(&msg, 5);
    // cout << msg;
}

Server::~Server() {
}
