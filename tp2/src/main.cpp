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

using namespace std;

void generate_std_funs(Functions &funs) {
    funs["+"] = add;
    funs["-"] = sub;
    funs["*"] = mul;
    funs["/"] = divv;
    funs["print"] = print;
    funs["setq"] = setq;
    funs["dummy"]  = dummy;
}

int main() {
    Functions funs;
    generate_std_funs(funs);
    Context ctxt;
    string input, res;
    queue<Thread*> parsers;
    while (getline(cin, input)) {
        parsers.push(new Parser(funs, ctxt, input));
        parsers.back()->start();
    }

    Thread *p;
    while (!parsers.empty()){
        p = parsers.front();       
        p->join();
        parsers.pop();
        delete p;
    }
    return 0;
}
