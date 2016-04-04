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
#include <stack>
#include <sstream>
#include <string>
#include <vector>

#include "enviroment.h"
#include "lispFunctions.h"

using namespace std;

void replace_substr(string &input, const string old_str, const string new_str) {
    size_t index = 0;
    while ( (index = input.find(old_str, index))!= string::npos ) {
        input.replace(index, old_str.size(), new_str);
        index += new_str.size();
    }
}

stack<string> parse(string input) {
    replace_substr(input, "(", " ( "); 
    replace_substr(input, ")", " ) "); 
    stack<string> parsed;
    stringstream ss(input);
    string sub;
    cout << input << endl; 

    while (ss >> sub) {
        parsed.push(sub) ;
    }
    return parsed;
}

void eval(Enviroment &env, stack<string> &parsed) {
    int left = 0, right = 0;
    string element = parsed.top();
    if (element.compare(")")) right++;
    vector<string> args;
    while (element.compare("(") != 0) {
        if (element.compare(")")) right++;
        else if (env.count(element) > 0) {
            LispFunctionType fun = env.getFunctionType(element);
            LispFunction *l = LispFunctionFactory::newLispFunction(fun);
            string result = l->run(args);
        }

        parsed.pop();
    }
}
int main() {
    string input;
    getline(cin, input);
    stack<string> parsed = parse(input);
    Enviroment env;
    
    return 0;
}
/* 
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
*/
