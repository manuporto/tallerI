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


#include "context.h"

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


typedef map<string, LispFunctionType> Functions;

class LispFunction {
    protected:

        string process_value(string arg, PContext& pctxt) {
            if (pctxt.has_key(arg)) {
                return pctxt.get(arg);
            } else {
                return arg;
            }
        }

    public:

        virtual string run(const vector<string>& args, PContext& pctxt){
            throw "Not Implemented.";
        }
        virtual ~LispFunction() {}
};

class LispDummy: public LispFunction {
    public:

        virtual string run(const vector<string>& args, PContext& pctxt) {
            return "I'm a dummy function!";
        }

        virtual ~LispDummy() {}
};

class LispAdd: public LispFunction {
    public:

        virtual string run(const vector<string>& args, PContext& pctxt) {
            int result = atoi(process_value(args[0], pctxt).c_str());
            stringstream ss;

            for (size_t i = 1; i < args.size(); i++) {
                result += atoi(process_value(args[i], pctxt).c_str());
            }

            ss << result;
            return ss.str();
        }

        virtual ~LispAdd() {}
};

class LispSub: public LispFunction {
    public:

        virtual string run(const vector<string>& args, PContext& pctxt) {
            int result = atoi(process_value(args[0], pctxt).c_str());
            stringstream ss;

            for (size_t i = 1; i < args.size(); i++) {
                result -= atoi(process_value(args[i], pctxt).c_str());
            }

            ss << result;
            return ss.str();
        }
    
        
        virtual ~LispSub() {}
};

class LispMul: public LispFunction {
    public:
        virtual string run(const vector<string>& args, PContext& pctxt) {
            int result = atoi(process_value(args[0], pctxt).c_str());
            stringstream ss;

            for (size_t i = 1; i < args.size(); i++) {
                result *= atoi(process_value(args[i], pctxt).c_str());
            }

            ss << result;
            return ss.str();
        }        
        
        virtual ~LispMul() {}
};

class LispDiv: public LispFunction {
    public:
        virtual string run(const vector<string>& args, PContext& pctxt) {
            double result = strtod(process_value(args[0], pctxt).c_str(), 
                    NULL);
            stringstream ss;

            for (size_t i = 1; i < args.size(); i++) {
                result /= strtod(process_value(args[i], pctxt).c_str(), NULL);
            }

            ss << result;
            return ss.str();
        }        virtual ~LispDiv() {}
};

class LispPrint: public LispFunction {
    public:
        virtual string run(const vector<string>& args, PContext& pctxt) {
            for (size_t i = 0; i < args.size(); i++) {
                cout << process_value(args[i], pctxt);
                cout << " ";
            }
            cout << endl;
            return "";
        }
};

class LispSetq: public LispFunction {
    public:
        virtual string run(const vector<string>& args, PContext& pctxt) {
            //cout << "var name: " << args[0] << endl;
            //cout << "var value: " << args[1] << endl;
            pctxt.set(args[0], args[1]);
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
