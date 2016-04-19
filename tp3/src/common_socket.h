#ifndef SOCKET2_H
#define SOCKET2_H

typedef struct addrinfo addrinfo;

class Socket {
   public:
    Socket(addrinfo& res);
	Socket(int fd);
    void socket_bind(addrinfo& res);
    void socket_connect(addrinfo& res);
    void socket_listen(int backlog);
	Socket socket_accept();
    void socket_send(void* buf, int size);
    void socket_receive(void* buf, int size);
    ~Socket();

   private:
    void process_message(void* buf, int size, int mode);
    int fd;
};

#endif  // SOCKET2_H
