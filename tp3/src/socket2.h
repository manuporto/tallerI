#ifndef SOCKET2_H
#define SOCKET2_H

typedef struct addrinfo addrinfo;

class socket2 {
   public:
    socket2(string hostname, string port, addrinfo& res);
	socket2(int fd);
    void socket_bind(addrinfo& res);
    void socket_connect(addrinfo& res);
    void socket_listen(int backlog);
	socket2* socket_accept();
    void socket_send(void* buf, int size);
    void socket_receive(void* buf, int size);
    ~socket2();

   private:
    void process_message(void* buf, int size, int mode);
    int fd;
};

#endif  // SOCKET2_H
