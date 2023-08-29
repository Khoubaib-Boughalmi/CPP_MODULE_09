#ifndef BITCOINEXCHANGE_H
#define BITCOINEXCHANGE_H

#include <iostream>
#include <cstring>
#include <fstream>
#include <cstdlib>
#include <map>
#include <sstream>
#include <string>

struct s_date {
    long year;
    long month;
    long day;
    bool operator<(const s_date& other) const {
        if (year != other.year) return year < other.year;
        if (month != other.month) return month < other.month;
        return day < other.day;
    }
};

extern std::map<s_date, double>fInputMap;
#endif