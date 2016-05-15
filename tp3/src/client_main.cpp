#include "client_client.h"

int main(int argc, char **argv) {
    if (argc != 3) {
        return 1;
    }
    Client cl(argv[1], argv[2]);
    return 0;
}
