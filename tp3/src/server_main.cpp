#include "server_server.h"

int main(int argc, char** argv) {
    if (argc != 2) {
        return 1;
    }
    Server sv(argv[1]);
    sv.run();
    return 0;
}
