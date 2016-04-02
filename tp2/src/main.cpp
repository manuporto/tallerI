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

void lisp_add(const vector<int>& atoms, int& result) {
    for (size_t i = 0; i < atoms.size(); i++) {
        result += atoms[i];
    }

}
int main() {
    
    string str;
    getline(cin, str, '(');
    getline(cin, str, ')');
    istringstream iss(str);
    string sub;
    int op;
    iss >> sub;
    vector<int> atoms;
    while (iss >> op) {
        atoms.push_back(op);
        cout << "Substring: " << op << endl;
    }

    int result = 0;
    LispFunction *l = LispFunctionFactory::newLispFunction(
            LispFunctionFactory::add);
    l->run(atoms, result);
    cout << result << endl;
    return 0;
}
