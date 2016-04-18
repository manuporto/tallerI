#include <iostream>
#include <string>
#include <sstream>

#include "client.h"

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
	status = getaddrinfo(hostname, port, &hints, &res);	
	*skt = Socket(res);
	skt->socket_connect(res);
	get_input();
	}

void Client::get_input() {
    string input;
    while (getline(cin, input)) {
        process_input(input);
    }
	Socket s = skt_original.accept();
}

void Client::process_input(string input) {
    stringstream ss(input);
    string data;
    while (ss >> data) {
        cout << data << endl;
    }
}
Client::~Client() {}
