#include <iostream>
#include <string>
#include <sstream>

#include "client.h"

using std::cin;
using std::cout;
using std::string;
using std::stringstream;

Client::Client(string ip, string port) : ip(ip), port(port){
    process_input();
}

void Client::get_input() {
    string input;
    stringstream ss;
    while (getline(cin, input)) {
        ss << input;
        cout << ss.str();
    }
}

void Client::process_input(){


}
Client::~Client(){}
