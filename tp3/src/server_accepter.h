#ifndef ACCEPTER_H
#define ACCEPTER_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <queue>
#include <string>

#include "common_socket.h"
#include "server_ptemperatures.h"
#include "server_receiver.h"
#include "server_thread.h"  // Base class: Thread

using std::queue;
using std::string;

typedef queue<Receiver*> Receivers;

class Accepter : public Thread {
   public:
    Accepter(string port, PTemperatures& tmpts);
    void join();
    virtual void run();
    ~Accepter();

   private:
    Socket* sv_skt;
    addrinfo* res;
    PTemperatures& tmpts;
    Receivers rcivrs;
    
};

#endif  // ACCEPTER_H
