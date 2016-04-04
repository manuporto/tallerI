/*
 * ============================================================================
 *
 *       Filename:  enviroment.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/04/16 12:33:10
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * ============================================================================
 */

#ifndef _ENVIROMENT_H_
#define _ENVIROMENT_H_
#include <map>
#include <string>

#include "lispFunctions.h"

class Enviroment {
    private:
        map<string, LispFunctionType> env;

    public:
        Enviroment() {
            env.insert(pair<string, LispFunctionType>("+", add));
            env.insert(pair<string, LispFunctionType>("-", sub));
            env.insert(pair<string, LispFunctionType>("*", mul));
            env.insert(pair<string, LispFunctionType>("/", divv));
 
        }

        LispFunctionType getFunctionType(string key) {
            return env[key];
        }

        ~Enviroment() {}
};

#endif
