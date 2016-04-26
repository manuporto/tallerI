#ifndef RECEIVER_H
#define RECEIVER_H
#include <string>

#include "common_socket.h"
#include "server_ptemperatures.h"
#include "server_thread.h"

using std::string;

class Receiver : public Thread {
   public:
    Receiver(Socket* skt, PTemperatures& tmpts);
    virtual void run();
    ~Receiver();

   private:
    void parse_message(string& msg);
    City parse_value(string value);
    Socket* skt;
    PTemperatures& tmpts;
};

#endif  // RECEIVER_H
