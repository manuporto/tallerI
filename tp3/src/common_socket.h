#ifndef SOCKET2_H
#define SOCKET2_H

#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>

using std::string;

typedef struct addrinfo addrinfo;

class Socket {
   public:
    explicit Socket(addrinfo& res);
	explicit Socket(int fd);
    void socket_bind(addrinfo& res);
    void socket_connect(addrinfo& res);
    void socket_listen(int backlog);
	Socket* socket_accept();
    void socket_send(string& msg, size_t size);
    void socket_receive(string& msg);
    ~Socket();

   private:
    int fd;
};

#endif  // SOCKET2_H
