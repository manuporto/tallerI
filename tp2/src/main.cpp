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

#include "lispFunctions.h"

using namespace std;

int main() {
    
    string str;
    getline(cin, str, '(');
    getline(cin, str, ')');
    istringstream iss(str);
    map<string, LispFunctionType> env;
    env.insert(pair<string, LispFunctionType>("+", add));
    env.insert(pair<string, LispFunctionType>("-", sub));
    env.insert(pair<string, LispFunctionType>("*", mul));
    env.insert(pair<string, LispFunctionType>("/", div));
    string sub;
    int op;
    iss >> sub;
    LispFunctionType fun = env[sub];
    vector<int> atoms;
    while (iss >> op) {
        atoms.push_back(op);
        cout << "Substring: " << op << endl;
    }

    int result = 0;
    LispFunction *l = LispFunctionFactory::newLispFunction(fun);
    l->run(atoms, result);
    delete l;
    cout << result << endl;
    return 0;
}
