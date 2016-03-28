#include<string.h>
#include<stdlib.h>

#include "client.h"
#include "server.h"

#define CLIENT_ARGC 8 //argv[0] and argv[1] (mode) counted
#define SERV_ARGC 3

int main(int argc, char *argv[]) {
    if (strcmp(argv[1], "client") == 0 && argc == CLIENT_ARGC) {
        client(argv[2], argv[3], argv[4], argv[5], argv[6], atoi(argv[7]));
    } else if (strcmp(argv[1], "server") == 0 && argc == SERV_ARGC)  {
        server(argv[2]);
    } else {
        return 1;
    }
    
    return 0; 
}
