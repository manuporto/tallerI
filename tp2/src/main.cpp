#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <vector>

#include "lispFunctions.h"
#include "parser.h"
#include "thread.h"
#include "context.h"
#include "interpreter.h"

using std::cin;
using std::queue;
using std::string;

int main(int argc, char *argv[]) {
    if (argc > 1) {
        cout << "ERROR: argumentos" << endl;
        return 1;
    }
    Context ctxt;
    PContext pctxt(ctxt);
    Interpreter intprtr(pctxt);
    return intprtr.run();
}
