#ifndef PARSER_H
#define PARSER_H

#include <queue>
#include <string>
#include <vector>

#include "context.h"
#include "lispFunctions.h"
#include "thread.h"

using std::string;
using std::queue;

class Parser: public Thread {
    private:
        LispFunctionFactory funFactory;
        Functions &funs;
        PContext &pctxt;
        string input;
        

        void replace_substr(string &input, const string old_str,
                const string new_str) {
            size_t index = 0;
            while ( (index = input.find(old_str, index))!= string::npos ) {
                input.replace(index, old_str.size(), new_str);
                index += new_str.size();
            }
        }

        queue<string> separate_tokens() {
            replace_substr(input, "(", " ( ");
            replace_substr(input, ")", " ) ");
            queue<string> parsed;
            stringstream ss(input);
            string sub;

            while (ss >> sub) {
                parsed.push(sub);
            }
            return parsed;
        }
        string eval(queue<string> &parsed) {
            vector<string> args;
            LispFunction *l = funFactory.newLispFunction(dummy);
            string element, res;
            while (!parsed.empty()) {
                element = parsed.front();
                parsed.pop();
                if (element.compare(")") == 0) {
                    res = l->run(args, pctxt);
                    return res;
                } else if (element.compare("(") == 0) {
                    res = eval(parsed);
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
        Parser(Functions &funs, PContext &pctxt, string input) : 
            funs(funs), pctxt(pctxt), input(input) {
            funFactory = LispFunctionFactory();
        }

        void run() {
            queue<string> parsed = separate_tokens();
            eval(parsed);
        }

        virtual ~Parser() {}
};

#endif
