/*
 * ============================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  31/03/16 21:29:25
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Autor:  Porto, Manuel Ignacio
 *         Padron: 96587
 *
 * ============================================================================
 */

#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <vector>

#include "lispFunctions.h"
#include "parser.h"
#include "thread.h"
#include "context.h"

using std::cin;
using std::queue;
using std::string;

typedef queue<Thread*> Threads;
void generate_std_funs(Functions &funs) {
    funs["+"] = add;
    funs["-"] = sub;
    funs["*"] = mul;
    funs["/"] = divv;
    funs["print"] = print;
    funs["setq"] = setq;
    funs["list"] = list;
    funs["car"] = car;
    funs["cdr"] = cdr;
    funs["append"] = append;
    funs["if"] = iff;
    funs["dummy"]  = dummy;
}

bool input_contains_errors(string input) {
    int pleft = 0;
    int pright = 0;
    for (size_t i = 0; i < input.size(); ++i) {
        if (input[i] == '(') ++pleft;
        else if (input[i] == ')') ++pright;
    }

    return pleft != pright;
}

void join_threads(Threads& threads) {
    Thread *p;
    while (!threads.empty()) {
        p = threads.front();       
        p->join();
        threads.pop();
        delete p;
    } 
}

int main(int argc, char *argv[]) {
    if (argc > 1) {
        cout << "ERROR: argumentos" << endl;
        return 1;
    }
    Functions funs;
    generate_std_funs(funs);
    Context ctxt;
    PContext pctxt(ctxt);
    string input, res;
    Threads parsers;
    while (getline(cin, input)) {
        if (input_contains_errors(input)) {
            cout << "ERROR: " << input << endl;
            join_threads(parsers);
            return 2;
        } else if (input.compare("(sync)") == 0) {
            join_threads(parsers);
        } else {
            parsers.push(new Parser(funs, pctxt, input));
            parsers.back()->start();
        }
    }
    
    join_threads(parsers);
    return 0;
}
