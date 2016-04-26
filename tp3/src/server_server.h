#ifndef SERVER_H
#define SERVER_H

#include <string>

#include "common_socket.h"
#include "server_presults.h"
#include "server_ptemperatures.h"

using std::string;

class Server {
   public:
    explicit Server(string port);
    void run();
    ~Server();

private:
    void get_data();
    void reduce();
    void print_results();
    string port;
    PTemperatures tmpts;
    PResults results;
};

#endif  // SERVER_H
