#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>

#include "socket_api.h"

int main() {
    sktinfo_t skt;

    socket_init(&skt, "127.0.0.1", "8080");
    socket_connect(&skt);
    char server_reply[256];
    socket_receive(&skt, server_reply, 256);
    puts(server_reply);
    char msg[] = "Cliente\n";
    socket_send(&skt, msg, strlen(msg));  
    socket_destroy(&skt);
    /*
    int socket_fd;
    struct sockaddr_in server;
    char *message, server_reply[2000];

    // Create socket
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (socket_fd == -1) {
        printf("Error\n");
        return 1;
    }

    server.sin_addr.s_addr = inet_addr("74.125.235.20");
    server.sin_family = AF_INET;
    server.sin_port = htons(80);

    if (connect(socket_fd, (struct sockaddr *)&server, sizeof(server)) < 0) {
        puts("Connection Error");
        return 1;
    }

    puts("Connected\n");

    // Send some data
    message = "GET / HTTP/1.1\r\n\r\n";
    if (send(socket_fd, message, strlen(message), 0) < 0) {
        puts("Send Error");
        return 1;
    }

    puts("Data sent!\n");

    // Receive reply
    if (recv(socket_fd, server_reply, 2000, 0) < 0) {
        puts("Recv Error");
        return 1;
    }
    puts("Received reply!\n");
    puts(server_reply);
    */   
    return 0;
}
