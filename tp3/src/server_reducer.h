#ifndef REDUCER_H
#define REDUCER_H

#include <string>

#include "server_thread.h" // Base class: Thread
#include "server_ptemperatures.h"

using std::string;

class Reducer : public Thread
{
public:
    Reducer(string day, PTemperatures& tmpts);
    ~Reducer();
private:
    Cities cities;
};

#endif // REDUCER_H
