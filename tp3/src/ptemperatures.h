#ifndef PTEMPERATURES_H
#define PTEMPERATURES_H

#include <map>
#include <utility>
#include <vector>

#include "mutex.h"

using std::map;
using std::pair;
using std::vector;

typedef pair<string, string> City;
typedef vector<City> Cities;
typedef map<string, Cities> Temperatures;

class PTemperatures
{
public:
    PTemperatures();
    void set(string key, string value);
    ~PTemperatures();
private:
    Temperatures tmpts;
    Mutex m;
};

#endif // PTEMPERATURES_H
