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
    PContext pctxt(ctxt);
    string input, res;
    queue<Thread*> parsers;
    Thread *p;
    while (getline(cin, input)) {
        if (input.compare("(sync)") == 0) {
            while (!parsers.empty()){
                p = parsers.front();       
                p->join();
                parsers.pop();
                delete p;
            }    
        } else {
            parsers.push(new Parser(funs, pctxt, input));
            parsers.back()->start();

        }
    }

    
    return 0;
}
