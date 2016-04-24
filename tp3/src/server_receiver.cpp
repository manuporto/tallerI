#include "common_socket.h"
#include "server_ptemperatures.h"
#include "server_receiver.h"

#include <iostream>
#include <sstream>
#include <string>

using std::cout;
using std::endl;
using std::make_pair;
using std::string;
using std::stringstream;

Receiver::Receiver(Socket* skt, PTemperatures& tmpts)
    : skt(skt), tmpts(tmpts) {}

void Receiver::run() {
    string msg, key, value;
    stringstream ss;
    skt->socket_receive(msg);
    while (msg.compare("End") != 0) {
        cout << msg << endl;
        ss << msg;
        ss >> key;
        ss >> value;
        City city_tmpt = parse_value(value);
        tmpts.set(key, city_tmpt);
        cout << city_tmpt.first << " " << city_tmpt.second << endl;
        ss.clear();
        skt->socket_receive(msg);
    }
}

City Receiver::parse_value(string value) {
    stringstream ss(value);
    string city, temperature;
    getline(ss, city, '-');
    ss >> temperature;
    return make_pair(city, temperature);
}
Receiver::~Receiver() { delete skt; }