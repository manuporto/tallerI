#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>

int main(int argc, char *argv[]) {
    // Creacion y conexion del socket
    struct addrinfo hints;
    struct addrinfo *res;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    getaddrinfo(argv[1], argv[2], &hints, res);
    int fd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    connect(fd, res->ai_addr, res->ai_addr_len);

    // Lectura y envio de archivo
    
    //FILE *fp = 
}
