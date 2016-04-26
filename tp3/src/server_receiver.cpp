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
    string msg = "";
    while (msg.compare("End") != 0) {
        skt->socket_receive(msg);
        parse_message(msg);
    }
}

void Receiver::parse_message(string& msg) {
    //cout << "Mensaje original: " << msg;
    //cout << "--------" << endl;
    string sub_msg, day, city_temp;
    stringstream ss;
    size_t pos = msg.find('\n');
    while (pos != string::npos) {
        sub_msg = msg.substr(0, pos);
        cout << sub_msg << endl;
        if (sub_msg.compare("End") == 0) {
            msg = sub_msg;
            return;
        }
        ss << sub_msg;
        ss >> day;
        ss >> city_temp;
        City city_tmpt = parse_value(city_temp);
        tmpts.set(day, city_tmpt);
        ss.clear();
        ss.str("");
        sub_msg.clear();
        msg = msg.substr(pos + 1);
        pos = msg.find('\n');
    }
    //cout << "FIN RECV" << endl;
}

City Receiver::parse_value(string value) {
    stringstream ss(value);
    string city, temperature;
    getline(ss, city, '-');
    ss >> temperature;
    return make_pair(city, temperature);
}
Receiver::~Receiver() { delete skt; }
