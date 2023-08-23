#ifndef BITCOINEXCHANGE_H
#define BITCOINEXCHANGE_H

#include <iostream>
#include <cstring>
#include <fstream>
#include <cstdlib>
#include <map>
#include <sstream>
#include <string>

typedef struct s_date {
    long year;
    long month;
    long day;
} t_date;

extern std::map<t_date, double>fInputMap;
#endif