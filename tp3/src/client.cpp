#include <iostream>
#include <string>
#include <sstream>

#include "client.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::stringstream;

Client::Client(string ip, string port) : ip(ip), port(port) { get_input(); }

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
