/*
 * ============================================================================
 *
 *       Filename:  parser.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/04/16 21:09:52
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * ============================================================================
 */

#include <queue>

#include "lispFunctions.h"
#include "enviroment.h"

class Parser {
    private:
        LispFunctionFactory funFactory;

        void replace_substr(string &input, const string old_str, 
                const string new_str) {
            size_t index = 0;
            while ( (index = input.find(old_str, index))!= string::npos ) {
                input.replace(index, old_str.size(), new_str);
                index += new_str.size();
            }
        }

        queue<string> separate_tokens(string input) {
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
        string eval(Functions &funs, Context ctxt, queue<string> &parsed) {
            vector<string> args;
            LispFunction *l = funFactory.newLispFunction(dummy);
            string element, res;
            while (!parsed.empty()) {
                element = parsed.front();
                parsed.pop();
                if (element.compare(")") == 0) {
                    res = l->run(args, ctxt);
                    return res; 
                } else if (element.compare("(") == 0) {
                    res = eval(funs, ctxt, parsed);
                    args.push_back(res);
                } else if (funs.count(element)) {
                    l = funFactory.newLispFunction(funs[element]);
                } else {
                    args.push_back(element);
                }
            }

                return res;
        }
    public:
        Parser() {
            funFactory = LispFunctionFactory();
        }

        string run(Functions &funs, Context ctxt, string input) {
            queue<string> parsed = separate_tokens(input);
            return eval(funs, ctxt, parsed);
        }
};
