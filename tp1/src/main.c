#include<string.h>
#include<stdlib.h>

#include "client.h"
#include "server.h"

int main(int argc, char *argv[]) {
    if (strcmp(argv[1], "client") == 0) cliente(argv[2], argv[3], argv[4], 
            argv[5], argv[6], atoi(argv[7]));
    else servidor(argv[2]);
    
    return 0; 
}
