#ifndef REDUCER_H
#define REDUCER_H

#include <string>
#include <vector>

#include "server_thread.h" // Base class: Thread
#include "server_ptemperatures.h"
#include "server_presults.h"

using std::string;
using std::vector;

class Reducer : public Thread
{
public:
    Reducer(string day, Cities cities, PResults& results);
    virtual void run();
    ~Reducer();
private:
    string calculate_max_temp();
    string sort_cities(vector<string>& cities_v);
    string day;
    Cities cities;
    PResults& results;
};

#endif // REDUCER_H
