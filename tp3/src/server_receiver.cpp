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
    string msg, day, city_temp;
    stringstream ss;
    skt->socket_receive(msg);
    while (msg.compare("End") != 0) {
        ss << msg;
        ss >> day;
        ss >> city_temp;
        City city_tmpt = parse_value(city_temp);
        tmpts.set(day, city_tmpt);
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