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

class LispFunction {
    public:
        virtual void run(const vector<int>& args, int& result) = 0;
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

class LispFunctionFactory {
    public:
        enum LispFunctionType {
            add
        };

        static LispFunction *newLispFunction(LispFunctionType type) {
            switch (type) {
                case add: 
                    return new LispAdd;
                    break;
                default:
                    throw "Invalid LispFunctionType.";
            }
        }
};
