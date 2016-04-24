#include <iostream>
#include <cstdio>
#include <netdb.h>

#include "common_socket.h"
#include "server_accepter.h"
#include "server_receiver.h"
#include "server_server.h"

using std::string;
using std::cout;
using std::endl;

Server::Server(string port) : port(port){
    PTemperatures tmpts;
}

void Server::run() {
    Accepter accptr(port, tmpts);
    accptr.start();
    char input;
    do {
        input = getchar();
    } while (input != 'q');
    cout << "Sali" << endl;
    //accptr.join();
    cout << "Joinee" << endl;
}

Server::~Server() {}
