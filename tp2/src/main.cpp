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

#include "enviroment.h"
#include "lispFunctions.h"
#include "parser.h"

using namespace std;

void generate_std_funs(Functions &funs) {
    funs.insert(pair<string, LispFunctionType>("+", add));
    funs.insert(pair<string, LispFunctionType>("-", sub));
    funs.insert(pair<string, LispFunctionType>("*", mul));
    funs.insert(pair<string, LispFunctionType>("/", divv));
    funs["dummy"]  = dummy; 

}
/*
void replace_substr(string &input, const string old_str, const string new_str) {
    size_t index = 0;
    while ( (index = input.find(old_str, index))!= string::npos ) {
        input.replace(index, old_str.size(), new_str);
        index += new_str.size();
    }
}

queue<string> parse(string input) {
    replace_substr(input, "(", " ( "); 
    replace_substr(input, ")", " ) "); 
    queue<string> parsed;
    stringstream ss(input);
    string sub;

    while (ss >> sub) {
        parsed.push(sub) ;
    }
    return parsed;
}

string eval(Functions &funs, queue<string> &parsed) {
    vector<string> args;
    LispFunction *l = LispFunctionFactory::newLispFunction(dummy);
    string element, res;
    while (!parsed.empty()) {
        element = parsed.front();
        parsed.pop();
        if (element.compare(")") == 0) {
            res = l->run(args);
            delete l;
            return res; 
        } else if (element.compare("(") == 0) {
            cout << "eval call" << endl;
            res = eval(funs, parsed);
            args.push_back(res);
        } else if (funs.count(element)) {
            cout << "lisp fun def" << endl;
            delete l;
            l = LispFunctionFactory::newLispFunction(funs[element]);
        } else {
            cout << "arg push" << endl;
            args.push_back(element);
        }
    }

    delete l;
    return res;
}
*/
int main() {
    string input;
    getline(cin, input);
    Functions funs;
    generate_std_funs(funs);
    Parser parser;
    string res = parser.run(funs, input);
    cout << res << endl;
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
