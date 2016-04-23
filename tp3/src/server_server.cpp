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
using std::endl;

Server::Server(string port)
{
    addrinfo hints;
    memset(&hints, 0, sizeof(addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    getaddrinfo(NULL, port.c_str(), &hints, &res);
    skt = new Socket(*res);
    skt->socket_bind(*res);
    skt->socket_listen(10);
    get_data();
}

void Server::get_data()
{
    Socket* c_skt = skt->socket_accept();
    size_t msglen;
    string msg;
    do {
        c_skt->socket_receive(&msglen, sizeof(msglen));
        c_skt->socket_receive(msg, msglen + 5);
        cout << msg << endl; 
    } while (msg.compare("End") != 0);
    delete c_skt;
}

Server::~Server()
{
    delete skt;
}
