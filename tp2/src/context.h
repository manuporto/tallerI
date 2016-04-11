/*
 * ============================================================================
 *
 *       Filename:  context.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/04/16 12:25:13
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * ============================================================================
 */

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

        string get(string key) {
            if (ctxt.count(key)) {
                return ctxt[key];
            } else {
                throw "Key doesn't exists.";
            }
        }

        bool has_key(string key) {
            return ctxt.count(key) == 1;
        }

        void set(string key, string value) {
            Lock l(m);
            ctxt[key] = value;
        }
};

#endif
