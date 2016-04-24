#include <iostream>

#include "server_server.h"

using std::cout;
using std::endl;

int main(int argc, char** argv) {
    if (argc != 2) {
        return 1;
    }
    Server sv(argv[1]);
    sv.run();
    return 0;
}