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
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "enviroment.h"
#include "lispFunctions.h"

using namespace std;

vector<string> parse(string line) {
    vector<string> exp;
 
    return exp;
}

int main() {
    string str, sub;
    getline(cin, str, '(');
    getline(cin, str, ')');
    istringstream iss(str);
    iss >> sub;
    Enviroment env;
    LispFunctionType fun = env.getFunctionType(sub);
    vector<string> atoms;
    while (iss >> sub) {
        atoms.push_back(sub);
        cout << "Substring: " << sub << endl;
    }

    LispFunction *l = LispFunctionFactory::newLispFunction(fun);
    string result = l->run(atoms);
    delete l;
    cout << result << endl;
    return 0;
}
