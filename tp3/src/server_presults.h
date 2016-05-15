#ifndef PRESULTS_H
#define PRESULTS_H

#include <map>
#include <string>

#include "mutex.h"

using std::map;
using std::string;

typedef map<int, string> Results;

class PResults
{
public:
    PResults();
    void set(int key, string value);
    bool get_if_has_key(int key, string& ret_value);
    ~PResults();
private:
    Results results;
    Mutex m;
};

#endif // PRESULTS_H
