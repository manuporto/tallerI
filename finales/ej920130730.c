#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>

#define PKT_SIZE 600

enum {SEND, RECV};

void process_msg(int skt, char buff[], int mode) {
    int size = sizeof(char) * PKT_SIZE;
    int processed = 0;
    int status = 0; 

    while (processed  < size) {
        if (mode == SEND) {
            status = send(skt, &buff[processed], size - processed, 0);
        } else  {
            status = recv(skt, &buff[processed], size - processed, 0);
        }
        if (status <= 0) {
            printf("ERROR\n");
            break;
        } else {
            processed += status;
        }
        if (buff[processed - 1] == '\n') {
            printf("Null char rcv, end of msg\n");
            break;
        }
         
    }
}

void negate_bits(char buff[]) {
    int i = 0;
    while (buff[i] != '\n') {
        char a = buff[i];
        buff[i] = ~a; 
        ++i;
    }
}

int main() {
    struct addrinfo hints;
    struct addrinfo *res;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    getaddrinfo(NULL, "8080", &hints, &res);

    int fd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    bind(fd, res->ai_addr, res->ai_addrlen);
    listen(fd, 1);
    int connection = accept(fd, NULL, NULL);

    char buff[PKT_SIZE];
    do {
    memset(buff, 0, sizeof(char) * PKT_SIZE);
    process_msg(connection, buff, RECV);
    printf("%s\n", buff);
    printf("%d\n", buff[0]);
    negate_bits(buff);
    printf("%d\n", buff[0]);
    process_msg(connection, buff, SEND);
    } while (buff[0] != '\n');

    freeaddrinfo(res);
    shutdown(connection, SHUT_RDWR);
    close(connection);
    close(fd);
    return 0;
}
