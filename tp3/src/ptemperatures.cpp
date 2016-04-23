#include "ptemperatures.h"

#include <map>
#include <utility>
#include <vector>

using std::map;
using std::pair;
using std::vector;

PTemperatures::PTemperatures()
{
}

void PTemperatures::set(string key, string value) {
    Lock l(m);
    tmpts[key].push_back(value);
    }
PTemperatures::~PTemperatures()
{
}

