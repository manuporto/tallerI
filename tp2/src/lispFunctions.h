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
    divv
};

class LispFunction {
    public:
        virtual string run(const vector<string>& args){
            throw "Not Implemented.";
        }
        virtual ~LispFunction() {}
};

class LispAdd: public LispFunction {
    public:
        virtual string run(const vector<string>& args) {
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
        virtual string run(const vector<string>& args) {
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
        virtual string run(const vector<string>& args) {
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
        virtual string run(const vector<string>& args) {
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

class LispFunctionFactory {
    public:
        static LispFunction* newLispFunction(LispFunctionType type) {
            switch (type) {
                case add: 
                    return new LispAdd;
                    break;
                case sub: 
                    return new LispSub;
                    break;
                case mul: 
                    return new LispMul;
                    break;
               case divv: 
                    return new LispDiv;
                    break;
                default:
                    throw "Invalid LispFunctionType.";
            }
        }
};

#endif
