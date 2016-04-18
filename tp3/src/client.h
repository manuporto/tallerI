#ifndef CLIENT_H
#define CLIENT_H

#include <string>

using std::string;

class Client {
    public:
        Client(string ip, string port);
        virtual ~Client();
    private:
        void get_input();
        void process_input(string input);
        string ip;
        string port;
};

#endif // CLIENT_H
