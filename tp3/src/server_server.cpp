#include <iostream>
#include <cstdio>
#include <netdb.h>
#include <sstream>

#include "common_socket.h"
#include "server_accepter.h"
#include "server_receiver.h"
#include "server_reducer.h"
#include "server_presults.h"
#include "server_server.h"

using std::string;
using std::stringstream;
using std::cout;
using std::endl;

Server::Server(string port) : port(port) { PTemperatures tmpts; }

void Server::run() {
    Accepter accptr(port, tmpts);
    accptr.start();
    char input;
    do {
        input = getchar();
    } while (input != 'q');
    accptr.join();

    PResults results;
    stringstream ss;
    string day;
    Cities cities;
    for (size_t i = 1; i <= 4; ++i) {
        ss << i;
        day = ss.str();
        if (tmpts.get_if_has_key(day, cities)) {
            Reducer reducer(day, cities, results);
            reducer.start();
            reducer.join();
        }
        ss.str("");
    }
    
    string res;
    for (size_t i = 1; i <= 4; ++i) {
        if (results.get_if_has_key((int) i, res)) {
            cout << i << ": " << res << endl;
            }
        }
}

Server::~Server() {}
