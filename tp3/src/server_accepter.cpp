#include <cstring>
#include <stdexcept>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#include "common_socket.h"
#include "server_accepter.h"

using std::string;

Accepter::Accepter(string port, PTemperatures& tmpts) : tmpts(tmpts) {
    addrinfo hints;
    memset(&hints, 0, sizeof(addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    getaddrinfo(NULL, port.c_str(), &hints, &res);
    sv_skt = new Socket(*res);
    sv_skt->socket_bind(*res);
    sv_skt->socket_listen(10);
    freeaddrinfo(res);
}

void Accepter::run() {
    while (true) {
        try {
            Socket* c_skt = sv_skt->socket_accept();
            rcivrs.push(new Receiver(c_skt, tmpts));
            rcivrs.back()->start();
        }
        catch (const std::runtime_error& e) {
            break;
        }
    }
}

void Accepter::join() {
    Receiver* rcivr;
    while (!rcivrs.empty()) {
        rcivr = rcivrs.front();
        rcivrs.pop();
        rcivr->join();
        delete rcivr;
    }
    delete sv_skt;
    Thread::join();
}

Accepter::~Accepter() {}
