#ifndef SERVER_H
#define SERVER_H

#include <string>

#include "common_socket.h"
#include "server_ptemperatures.h"

using std::string;

class Server {
   public:
    explicit Server(string port);
    void run();
    ~Server();

private:
    string port;
    PTemperatures tmpts;
};

#endif  // SERVER_H
