#include <string>

#include "server_presults.h"

using std::string;

PResults::PResults() {}

void PResults::set(int key, string value) {
    Lock l(m);
    results[key] = value;
}

bool PResults::get_if_has_key(int key, string& ret_value) {
    Lock l(m);
    if (results.count(key)) {
        ret_value = results[key];
        return true;
    }
    return false;
}

PResults::~PResults() {}
