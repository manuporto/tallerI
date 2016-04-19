#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
#include <sys/types.h>
#include <sys/common_socket.h>
#include <netdb.h>

#include "client_client.h"
#include "common_socket.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::stringstream;

Client::Client(string hostname, string port) { 
	addrinfo hints;
    memset(&hints, 0, sizeof(addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
	getaddrinfo(hostname.c_str(), port.c_str(), &hints, &res);	
	*skt = Socket(*res);
	skt->socket_connect(*res);
	get_input();
	}

void Client::get_input() {
    string input;
    while (getline(cin, input)) {
        process_input(input);
    }
}

void Client::process_input(string input) {
    stringstream ss(input);
    string data;
    while (ss >> data) {
        cout << data << endl;
    }
}
Client::~Client() {}
