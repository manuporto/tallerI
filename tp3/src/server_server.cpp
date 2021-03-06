#include <iostream>
#include <cstdio>
#include <netdb.h>
#include <sstream>
#include <string>
#include <vector>

#include "common_socket.h"
#include "server_accepter.h"
#include "server_receiver.h"
#include "server_reducer.h"
#include "server_presults.h"
#include "server_server.h"

#define MAX_REDUCERS 4
#define MARCH_DAYS 31

using std::string;
using std::stringstream;
using std::vector;
using std::cout;
using std::endl;

Server::Server(string port) : port(port) {
    PTemperatures tmpts;
    PResults results;
}

void Server::get_data() {
    Accepter accptr(port, tmpts);
    accptr.start();
    char input;
    do {
        input = getchar();
    } while (input != 'q');
    accptr.join();
}

void Server::reduce() {
    stringstream ss;
    string day;
    Cities cities;
    vector<Reducer*> reducers;
    Reducer* reducer;
    for (size_t i = 1; i <= MARCH_DAYS;) {
        for (size_t j = 0; j < MAX_REDUCERS && i <= MARCH_DAYS; ++j) {
            ss << i;
            day = ss.str();
            if (tmpts.get_if_has_key(day, cities)) {
                reducers.push_back(new Reducer(day, cities, results));
                reducers.back()->start();
            }
            ss.str("");
            ++i;
        }
        while (!reducers.empty()) {
            reducer = reducers.back();
            reducers.pop_back();
            reducer->join();
            delete reducer;
        }
    }
}

void Server::print_results() {
    string res;
    for (size_t i = 1; i <= MARCH_DAYS; ++i) {
        if (results.get_if_has_key((int)i, res)) {
            cout << i << ": " << res << endl;
        }
    }
}

void Server::run() {
    get_data();
    reduce();
    print_results();
}

Server::~Server() {}
