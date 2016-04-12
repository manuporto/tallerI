#ifndef _INTERPRETER_H
#define _INTERPRETER_H

#include <queue>
#include <string>

#include "context.h"
#include "lispFunctions.h"
#include "parser.h"
#include "thread.h"

using std::queue;
using std::string;
using std::cin;

class Interpreter {
    private:
        Functions funs;
        typedef queue<Thread*> Threads;
        Threads parsers;
        PContext &pctxt;

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

    public:
        explicit Interpreter(PContext &pctxt) : pctxt(pctxt) {
            generate_std_funs(funs);
        }

        int run() {
            string input;
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
            return 0;
        }

        ~Interpreter() {
            join_threads(parsers);
        }
};

#endif
