#ifndef RECEIVER_H
#define RECEIVER_H

#include "common_socket.h"
#include "server_ptemperatures.h"
#include "server_thread.h"

class Receiver : public Thread
{
public:
    Receiver(Socket* skt, PTemperatures& tmpts);
    virtual void run();
    ~Receiver();
private:
    City parse_value(string value);
    Socket* skt;
    PTemperatures& tmpts;
};

#endif // RECEIVER_H
