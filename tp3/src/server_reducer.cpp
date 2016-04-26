#include "server_reducer.h"

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;

Reducer::Reducer(string day, Cities cities, PResults& results)
    : day(day), cities(cities), results(results) {}

void Reducer::run() {
    string res = calculate_max_temp();
    results.set(atoi(day.c_str()), res);
    }

string Reducer::calculate_max_temp() {
    vector<string> max_cities;
    max_cities.push_back(cities[0].first);
    int max_temp = atoi(cities[0].second.c_str());
    string s_max_temp = cities[0].second;
    int temp;
    string city;
    for (size_t i = 1; i < cities.size(); ++i) {
        city = cities[i].first;
        temp = atoi(cities[i].second.c_str());
        if (temp > max_temp) {
            s_max_temp = cities[i].second;
            max_temp = temp;
            max_cities.clear();
            max_cities.push_back(city);
        } else if (temp == max_temp) {
            max_cities.push_back(city);
        }
    }
    string res = sort_cities(max_cities);
    res += string(" (") + s_max_temp + string(")");
    //cout << "REDUCER: " << day << res << endl;
    return res;
}

string Reducer::sort_cities(vector<string>& cities_v) {
    std::sort(cities_v.begin(), cities_v.end());
    string sorted_cities = "";
    size_t i;
    for (i = 0; i < cities_v.size() - 1; ++i) {
        sorted_cities += cities_v[i] + "/";
    }

    sorted_cities += cities_v[i];
    return sorted_cities;
}

Reducer::~Reducer() {}
