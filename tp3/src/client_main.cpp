#include <iostream>

#include "client_client.h"

using std::cin;
using std::cout;
using std::endl;

int main(int argc, char **argv) {
    if (argc != 3) {
        return 1;
    }
    Client cl(argv[1], argv[2]);
    return 0;
}
