/*
 * ============================================================================
 *
 *       Filename:  functions.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  02/04/16 12:38:30
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (),
 *   Organization:
 *
 * ============================================================================
 */
#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 1
#endif

#ifndef _LISP_FUNCTIONS_H
#define _LISP_FUNCTIONS_H

#include <map>
#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <vector>



using namespace std;
enum LispFunctionType {
    add,
    sub,
    mul,
    divv,
    dummy,
    print,
    setq
};

typedef map<string, string> Context;
typedef map<string, LispFunctionType> Functions;

class LispFunction {
    public:
        virtual string run(const vector<string>& args, Context& ctxt){
            throw "Not Implemented.";
        }
        virtual ~LispFunction() {}
};

class LispDummy: public LispFunction {
    public:
        virtual string run(const vector<string>& args, Context& ctxt) {
            return "I'm a dummy function!";
        }

        virtual ~LispDummy() {}
};

class LispAdd: public LispFunction {
    public:
        virtual string run(const vector<string>& args, Context& ctxt) {
            int result = atoi(args[0].c_str());
            stringstream ss;
            for (size_t i = 1; i < args.size(); i++) {
               result += atoi(args[i].c_str());
            }

            ss << result;
            return ss.str();
        }

        virtual ~LispAdd() {}
};

class LispSub: public LispFunction {
    public:
        virtual string run(const vector<string>& args, Context& ctxt) {
            int result = atoi(args[0].c_str());
            stringstream ss;
            for (size_t i = 1; i < args.size(); i++) {
               result -= atoi(args[i].c_str());
            }

            ss << result;
            return ss.str();
        }

        virtual ~LispSub() {}
};

class LispMul: public LispFunction {
    public:
        virtual string run(const vector<string>& args, Context& ctxt) {
            int result = atoi(args[0].c_str());
            stringstream ss;
            for (size_t i = 1; i < args.size(); i++) {
               result *= atoi(args[i].c_str());
            }

            ss << result;
            return ss.str();
        }

        virtual ~LispMul() {}
};

class LispDiv: public LispFunction {
    public:
        virtual string run(const vector<string>& args, Context& ctxt) {
            double result = strtod(args[0].c_str(), NULL);
            stringstream ss;
            for (size_t i = 1; i < args.size(); i++) {
                result /= strtod(args[i].c_str(), NULL);
            }

            ss << result;
            return ss.str();
        }

        virtual ~LispDiv() {}
};

class LispPrint: public LispFunction {
    public:
        virtual string run(const vector<string>& args, Context& ctxt) {
            for (size_t i = 0; i < args.size(); i++) {
                if (ctxt.count(args[i])) {
                    cout << ctxt[args[i]];
                } else {
                    cout << args[i];
                }
            }
            cout << endl;
            return "";
        }
};

class LispSetq: public LispFunction {
    public:
        virtual string run(const vector<string>& args, Context& ctxt) {
            //cout << "var name: " << args[0] << endl;
            //cout << "var value: " << args[1] << endl;
            ctxt[args[0]] = args[1];
            return "";
        }
};

class LispFunctionFactory {
    private:
        vector<LispFunction*> functions;

    public:
        LispFunction* newLispFunction(LispFunctionType type) {
            LispFunction *l;
            switch (type) {
                case add:
                    l = new LispAdd;
                    break;
                case sub:
                    l = new LispSub;
                    break;
                case mul:
                    l = new LispMul;
                    break;
                case divv:
                    l = new LispDiv;
                    break;
                case print:
                    l = new LispPrint;
                    break;
                case setq:
                    l = new LispSetq;
                    break;
                case dummy:
                    l = new LispDummy;
                    break;
                default:
                    throw "Invalid LispFunctionType.";
            }

            functions.push_back(l);
            return l;
        }

        ~LispFunctionFactory() {
            for (size_t i = 0; i < functions.size(); i++) {
                delete functions[i];
            }
            return;
        }
};

#endif
