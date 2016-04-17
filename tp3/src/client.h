#ifndef CLIENT_H
#define CLIENT_H

#import <string>

using std::string;

class Client {
    public:
        Client(string ip, string port);
        virtual ~Client();
    private:
        void get_input();
        void process_input();
        string ip;
        string port;
};

#endif // CLIENT_H
