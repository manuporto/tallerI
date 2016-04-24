#ifndef SERVER_H
#define SERVER_H

#include <string>

#include "common_socket.h"
#include "server_ptemperatures.h"

using std::string;

class Server {
   public:
    Server(string port);
    ~Server();

private:
    void get_data();
    Socket* sv_skt;
    addrinfo* res;
    PTemperatures tmpts;
};

#endif  // SERVER_H
