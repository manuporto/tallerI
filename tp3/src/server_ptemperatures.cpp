#include "server_ptemperatures.h"

#include <map>
#include <string>
#include <utility>
#include <vector>

using std::map;
using std::pair;
using std::string;
using std::vector;

PTemperatures::PTemperatures() {}

void PTemperatures::set(string key, City value) {
    Lock l(m);
    tmpts[key].push_back(value);
}

bool PTemperatures::get_if_has_key(string& key, Cities& ret_value) {
    Lock l(m);
    if (tmpts.count(key)) {
        ret_value = tmpts[key];
        return true;
    }
    return false;
}

PTemperatures::~PTemperatures() {}
