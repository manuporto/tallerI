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
#include "mutex.h"

using std::cout;
using std::endl;
using std::string;
using std::stringstream;
using std::map;
using std::vector;

enum LispFunctionType {
    add,
    sub,
    mul,
    divv,
    dummy,
    print,
    setq,
    list,
    car,
    cdr,
    append,
    iff
};


typedef map<string, LispFunctionType> Functions;

class LispFunction {
    protected:
        string process_value(string arg, PContext& pctxt) {
            string res;
            if (pctxt.get_if_has_key(arg, res)) {
                return res;
            } 
            return arg;
        }

    public:
        virtual string run(const vector<string>& args, PContext& pctxt) = 0;
        virtual ~LispFunction() {}
};

class LispDummy: public LispFunction {
    public:
        virtual string run(const vector<string>& args, PContext& pctxt) {
            return "ERROR: This class it must not be used";
        }
};

class LispArithmetic: public LispFunction {
    protected:
        typedef int (*arithmetic_fun)(int, int);
        int calculate(const vector<string>& args, PContext& pctxt, 
                arithmetic_fun operation) {
            int result = atoi(process_value(args[0], pctxt).c_str());
            int argument;
            for (size_t i = 1; i < args.size(); ++i) {
                argument = atoi(process_value(args[i], pctxt).c_str());
                result = operation(result, argument);
            }
            return result;
        }
};

class LispAdd: public LispArithmetic {
    private:
        static int add(int a, int b) {
            return a + b;
        }

    public:
        virtual string run(const vector<string>& args, PContext& pctxt) {
            int result = calculate(args, pctxt, add);
            stringstream ss;
            ss << result;
            return ss.str();
        }
};

class LispSub: public LispArithmetic {
    private:
        static int sub(int a, int b) {
            return a - b;
        }

    public:
        virtual string run(const vector<string>& args, PContext& pctxt) {
            int result = calculate(args, pctxt, sub);
            stringstream ss;
            ss << result;
            return ss.str();
        }
};

class LispMul: public LispArithmetic {
    private:
        static int mul(int a, int b) {
            return a * b;
        }

    public:
        virtual string run(const vector<string>& args, PContext& pctxt) {
            int result = calculate(args, pctxt, mul);
            stringstream ss;
            ss << result;
            return ss.str();
        }
};

class LispDiv: public LispFunction {
    public:
        virtual string run(const vector<string>& args, PContext& pctxt) {
            double result = strtod(process_value(args[0], pctxt).c_str(), 
                    NULL);
            stringstream ss;

            for (size_t i = 1; i < args.size(); ++i) {
                result /= strtod(process_value(args[i], pctxt).c_str(), NULL);
            }

            ss << result;
            return ss.str();
        }        
};

class LispPrint: public LispFunction {
    private:
        static Mutex m;

    public:
        virtual string run(const vector<string>& args, PContext& pctxt) {
            Lock l(m);
            size_t i;
            for (i = 0; i < args.size() - 1; ++i) {
                cout << process_value(args[i], pctxt);
                cout << " ";
            }
            cout << process_value(args[i], pctxt) << endl;
            return "";
        }
};
Mutex LispPrint::m;

class LispSetq: public LispFunction {
    public:
        virtual string run(const vector<string>& args, PContext& pctxt) {
            pctxt.set(args[0], args[1]);
            return "";
        }
};

class LispLists: public LispFunction {
    protected:
        size_t head_end_index(string elements) {
            int pleft = 0;
            int pright = 0;
            size_t i;
            for (i = 0; i < elements.size(); ++i) {
                if (elements[i] == ' ' && pleft == pright) {
                    break;
                } else if (elements[i] == '(') {
                    ++pleft;
                } else if (elements[i] == ')') {
                    ++pright;
                }
            }
            return i;
        }

        void delete_outer_parenthesis(string& elements) {
            elements.replace(0, 1, "");
            elements.replace(elements.size() - 1, 1, "");
        }
};

class LispList: public LispLists {
    public:
        virtual string run(const vector<string>& args, PContext& pctxt) {
            if (args.size() == 0) {
                return "()";
            }
            string res = "(";
            size_t i;
            for (i = 0; i < args.size() - 1; ++i) {
                res += process_value(args[i], pctxt) + " ";
            }    
            res += process_value(args[i], pctxt) + ")";
            return res;
        }
};

class LispCar: public LispLists {
    public:
        virtual string run(const vector<string>& args, PContext& pctxt) {
            string elements = process_value(args[0], pctxt);
            if (elements.compare("()") == 0) {
                return elements;
            }
            delete_outer_parenthesis(elements);
            size_t index = head_end_index(elements);
            return elements.substr(0, index);
        }
};

class LispCdr: public LispLists {
    public:
        virtual string run(const vector<string>& args, PContext& pctxt) {
            string elements = process_value(args[0], pctxt);
            if (elements.compare("()") == 0) {
                return elements;
            }
            delete_outer_parenthesis(elements);
            size_t index = head_end_index(elements);
            return "(" + elements.substr(index + 1) + ")";
        }
};

class LispAppend: public LispLists {
    public:
        virtual string run(const vector<string>& args, PContext& pctxt) {
            string elements; 
            string res = "(";
            size_t i;
            for (i = 0; i < args.size() - 1; ++i) {
                elements = process_value(args[i], pctxt);
                delete_outer_parenthesis(elements);
                if (elements.compare("") == 0) {
                    res += elements;
                } else {
                    res += elements + " ";
                }
            }
            elements = process_value(args[i], pctxt);
            delete_outer_parenthesis(elements);
            res += elements + ")";
            return res;
        } 
};

class LispIf: public LispFunction {
    public:
        virtual string run(const vector<string>& args, PContext& pctxt) {
            string condition = process_value(args[0], pctxt);
            string true_value = process_value(args[1], pctxt); 
            string false_value = process_value(args[2], pctxt); 
            if (condition.compare("()") != 0) {
                return true_value;
            }

            return false_value;
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
                 case list:
                    l = new LispList;
                    break;
                  case car:
                    l = new LispCar;
                    break;               
                  case cdr:
                    l = new LispCdr;
                    break;               
                  case append:
                    l = new LispAppend;
                    break;               
                  case iff:
                    l = new LispIf;
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
            for (size_t i = 0; i < functions.size(); ++i) {
                delete functions[i];
            }
            return;
        }
};

#endif
