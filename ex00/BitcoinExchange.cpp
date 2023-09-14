#include "BitcoinExchange.hpp"


long populateYear(std::string year) {
    long yearVal;

    year = strTrim(const_cast<char *>(year.c_str()));
    yearVal = std::strtol(year.c_str(), NULL, 10);
    return yearVal;
}

double pulateValue(std::string value) {
    double valueVal;

    value = strTrim(const_cast<char *>(value.c_str()));
    valueVal = std::strtod(value.c_str(), NULL);
    return valueVal;
}

int confirmDate(s_date inputDate, s_date dataDate) {
    if (inputDate.year == dataDate.year && \
        inputDate.month == dataDate.month && \
        inputDate.day == dataDate.day)
        return (1);
    return (0);
}

void closestBitcoinExchange(std::string date, double value) {
    (void)date;
    (void)value;
    std::map<std::string, double>::iterator prevIt;
    std::map<std::string, double>::iterator currIt;
    currIt = fDataMap.begin();
    if(currIt != fDataMap.end()) {

        if(date < currIt->first)
            std::cout << date << " ==> " << value << " = " << currIt->second * value << std::endl;
        else
        {
            for (; currIt != fDataMap.end(); currIt++)
            {
                if(currIt->first > date)
                    break;
                prevIt = currIt;
            }
            std::cout << date << " ==> " << value << " = " << prevIt->second * value << std::endl;
        }
    }
}

void BitcoinExchange(std::string date, double value) {
    std::map<std::string, double>::iterator it;
    it = fDataMap.begin();
    int found = 0;
    for (it = fDataMap.begin(); it != fDataMap.end(); it++)
    {
        if(date == it->first)
        {
            found = 1;
            break;
        }
    }
    if(found)
        std::cout << date << " ==> " << value << " = " << it->second * value << std::endl;
    else
        closestBitcoinExchange(date, value);
}

void calculateExchangeRateFun(std::string date, double value) {
    BitcoinExchange(date, value);
}

void populateFInputMap(std::string date, std::string value, std::map<std::string, double> &fInputMap, bool calculateExchangeRate) {
    std::istringstream iss(date);
    std::string token;
    date = strTrim(const_cast<char *>(date.c_str()));
    fInputMap[date] = pulateValue(value);
    if(calculateExchangeRate)
        calculateExchangeRateFun(date, fInputMap[date]);
}