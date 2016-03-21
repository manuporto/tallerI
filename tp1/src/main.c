#include<string.h>

#include "cliente.h"
#include "servidor.h"

int main(int argc, char *argv[]) {
    if (strcmp(argv[1], "cliente") == 0) cliente();
    else servidor();
    
    return 0; 
}
