#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#include "common_socket.h"

using std::string;

class Client {
    public:
        Client(string hostname, string port);
        virtual ~Client();
    private:
        void get_input();
        void process_input(string input);
        Socket* skt;
        addrinfo* res;
};

#endif // CLIENT_H
