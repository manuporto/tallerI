#include <iostream>
#include <cstdio>
#include <netdb.h>
#include <sstream>
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

Server::Server(string port) : port(port)
{
    PTemperatures tmpts;
}

void Server::run()
{
    // Get data
    Accepter accptr(port, tmpts);
    accptr.start();
    char input;
    do {
        input = getchar();
    } while (input != 'q');
    accptr.join();

    // Reduce
    PResults results;
    stringstream ss;
    string day;
    Cities cities;
    vector<Reducer*> reducers;
    Reducer* reducer;
    for (size_t i = 1; i <= MARCH_DAYS; ++i) {

        for (size_t j = 0; j < MAX_REDUCERS && i <= MARCH_DAYS; ++j) {
            ss << i;
            day = ss.str();
            if (tmpts.get_if_has_key(day, cities)) {
                reducers.push_back(new Reducer(day, cities, results));
                reducers.back()->start();
            }
            ss.str("");
        }
        while (!reducers.empty()) {
            reducer = reducers.back();
            reducers.pop_back();
            reducer->join();
            delete reducer;
        }
    }

    // Print results
    string res;
    for (size_t i = 1; i <= MARCH_DAYS; ++i) {
        if (results.get_if_has_key((int)i, res)) {
            cout << i << ": " << res << endl;
        }
    }
}

Server::~Server()
{
}
