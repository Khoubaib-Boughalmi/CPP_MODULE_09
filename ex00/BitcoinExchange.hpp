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

std::string strTrim(char * passedStr);
int checkNumberOccurrences(std::string str, char c);
void parseSingleLine(std::map<std::string, std::string> &uMap, std::string line, char sep);
int validateData(std::map<std::string, std::string> &uMap);
int checkYear(std::string year);
int checkMonth(std::string month);
int checkDay(std::string day);
int validateDate(std::map<std::string, std::string> &uMap);
int validateValues(std::map<std::string, std::string> &uMap, bool isInputData);
int parseInput(std::string line, std::map<std::string, double> &fMap, char sep);
int parseFirstLine(std::string str, const char *val1, const char *val2, char sep);
void populateFInputMap(std::string date, std::string value, std::map<std::string, double> &fInputMap, bool calculateExchangeRate);
void calculateExchangeRateFun(std::string date, double value);
void BitcoinExchange(std::string date, double value);
void closestBitcoinExchange(std::string date, double value);
int confirmDate(s_date inputDate, s_date dataDate);
double pulateValue(std::string value);
long populateYear(std::string year);



extern std::map<s_date, double>fInputMap;
extern std::map<std::string, double>fDataMap;

#endif