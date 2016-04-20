#ifndef SERVER_H
#define SERVER_H

#include <string>

#include "common_socket.h"

using std::string;

class Server {
   public:
    Server(string port);
    ~Server();

   private:
    Socket* skt;
    addrinfo* res;
};

#endif  // SERVER_H
