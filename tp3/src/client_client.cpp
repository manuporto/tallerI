#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#include "client_client.h"
#include "common_socket.h"

using std::cin;
using std::string;
using std::stringstream;

Client::Client(string hostname, string port) {
    addrinfo hints;
    memset(&hints, 0, sizeof(addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = 0;
    getaddrinfo(hostname.c_str(), port.c_str(), &hints, &res);
    skt = new Socket(*res);
    skt->socket_connect(*res);
    freeaddrinfo(res);
    get_input();
}

void Client::get_input() {
    string input;
    while (getline(cin, input)) {
        process_input(input);
    }
    string end = "End\n";
    size_t l = end.size();
    skt->socket_send(end, l);
}

void Client::process_input(string input) {
    stringstream ss(input);
    string data, key, value;
    ss >> data;
    value.append(data);
    ss >> data;
    value.append("-");
    value.append(data);
    ss >> key;
    key += " " + value + "\n";
    skt->socket_send(key, key.size());
}
Client::~Client() { delete skt; }
