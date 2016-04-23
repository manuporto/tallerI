#ifndef _CONTEXT_H
#define _CONTEXT_H

#include <map>
#include <string>

#include "mutex.h"
#include "lispFunctions.h"

using std::map;
using std::string;

typedef map<string, string> Context;

class PContext {
    private:
        Mutex m;
        Context &ctxt;

    public:
        explicit PContext(Context &ctxt) : ctxt(ctxt) {}

        void set(string key, string value) {
            Lock l(m);
            ctxt[key] = value;
        }

        bool get_if_has_key(string &key, string &ret_value) {
            Lock l(m);
            if (ctxt.count(key)) {
                ret_value = ctxt[key];
                return true;
            }
            return false;
        }
};

#endif
