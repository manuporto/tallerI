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

#include <vector>

using namespace std;
enum LispFunctionType {
    add,
    sub,
    mul,
    div
};

class LispFunction {
    public:
        virtual void run(const vector<int>& args, int& result){
            throw "Not Implemented.";
        }
        virtual ~LispFunction() {}
};

class LispArithmeticFunction: public LispFunction {
    public:
        virtual void run(const vector<int>& args, int& result) = 0;
        virtual ~LispArithmeticFunction() {}
};

class LispAdd: public LispArithmeticFunction {
    public:
        virtual void run(const vector<int>& args, int& result) {
            for (size_t i = 0; i < args.size(); i++) {
               result += args[i];
            } 
        }

        virtual ~LispAdd() {}
};

class LispSub: public LispArithmeticFunction {
    public:
        virtual void run(const vector<int>& args, int& result) {
            for (size_t i = 0; i < args.size(); i++) {
               result -= args[i];
            } 
        }

        virtual ~LispSub() {}
};

class LispMul: public LispArithmeticFunction {
    public:
        virtual void run(const vector<int>& args, int& result) {
            result = args[0];
            for (size_t i = 1; i < args.size(); i++) {
               result *= args[i];
            } 
        }

        virtual ~LispMul() {}
};

class LispDiv: public LispArithmeticFunction {
    public:
        virtual void run(const vector<int>& args, int& result) {
            result = args[0];
            for (size_t i = 1; i < args.size(); i++) {
               result /= args[i];
            } 
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
               case div: 
                    return new LispDiv;
                    break;
                default:
                    throw "Invalid LispFunctionType.";
            }
        }
};
