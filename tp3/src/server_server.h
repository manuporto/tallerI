#ifndef SERVER_H
#define SERVER_H

class Server {
   public:
    Server(string port);
    ~Server();

   private:
    Socket* skt;
    addrinfo* res;
};

#endif  // SERVER_H
