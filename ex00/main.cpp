#include "BitcoinExchange.h"

std::string strTrim(char * passedStr) {
    size_t start; 
    size_t end;

    if(!passedStr || !passedStr[0])
        return "";
    std::string str(passedStr);
    start = str.find_first_not_of(" \t\r"); 
    if(start == std::string::npos)
        return "";
    end = str.find_last_not_of(" \t\r"); 
    return str.substr(start, end - start + 1);
}

int checkNumberOccurrences(std::string str, char c) {
    int count = 0;
    for (size_t i = 0; i < str.length(); i++)
    {
        if(str[i] == c)
            count++;
    }
    return (count);
}

void parseSingleLine(std::map<std::string, std::string> &uMap, std::string line, char sep) {
    char *token = NULL;
    char *key = const_cast<char*>("");
    char *value = const_cast<char*>("");
    int setErr = 0;
    char strSep[2] = {sep, '\0'};
    if(checkNumberOccurrences(line, sep) > 1)
        setErr = 1;
    if(!strcmp(strTrim(const_cast<char *>(line.c_str())).c_str(), strSep))
        setErr = 1;
    if(strTrim(const_cast<char *>(line.c_str()))[0] == sep)
        setErr = 1;
    if(!setErr)
    {
        token = std::strtok(const_cast<char *>(line.c_str()), strSep);
        if(token && token[0])
            key = token;
        else
            return ;
        std::string str;
        if(!strTrim(token).empty())
        {
            token = std::strtok(NULL, "|");
            if(token)
                value = token;
            else
                value = const_cast<char*>("\0");
        }
        uMap[key] = value;
    }
    else
        uMap[const_cast<char*>("\0")] = const_cast<char*>("\0");
}

int validateData(std::map<std::string, std::string> &uMap) {
    std::map<std::string, std::string>::iterator it;
    it = uMap.begin();
    if(!it->first[0] || !it->second[0])
    {
        std::cout << "Error with input data" << std::endl;
        return (0);
    }
    return (1);
}

int checkYear(std::string year) {
    long yearVal;
    char *ptr;

    year = strTrim(const_cast<char *>(year.c_str()));
    if(std::strlen(year.c_str()) != 4)
        return (0);
    yearVal = std::strtol(year.c_str(), &ptr, 10);
    if(*ptr != '\0')
        return (0);
    if(yearVal < 1970 || yearVal > 2069)
        return (0);
    return (1);
}

int checkMonth(std::string month) {
    long monthVal;
    char *ptr;

    month = strTrim(const_cast<char *>(month.c_str()));
    if(std::strlen(month.c_str()) != 2)
        return (0);
    monthVal = std::strtol(month.c_str(), &ptr, 10);
    if(*ptr != '\0')
        return (0);
    if(monthVal < 1 || monthVal > 12)
        return (0);
    return (1);
}

int checkDay(std::string day) {
    long dayVal;
    char *ptr;

    day = strTrim(const_cast<char *>(day.c_str()));
    if(std::strlen(strTrim(const_cast<char *>(day.c_str())).c_str()) != 2)
        return (0);
    dayVal = std::strtol(day.c_str(), &ptr, 10);
    if(*ptr != '\0')
        return (0);
    if(dayVal < 1 || dayVal > 31)
        return (0);
    return (1);
}

int validateDate(std::map<std::string, std::string> &uMap) {
    int counter = 0;
    (void)uMap;
    std::map<std::string, std::string>::iterator it;
    it = uMap.begin();
    std::string date = it->first;
    if (checkNumberOccurrences(date, '-') != 2)
        return (0);
    char *token = std::strtok(const_cast<char *>(date.c_str()), "-");
    while (token)
    {
        switch (counter) {
            case 0:
                if (!checkYear(token)) { std::cout << "Error: Year value is incorrect" << std::endl; return (0);}
                break ;
            case 1:
                if (!checkMonth(token)){ std::cout << "Error: Month value is incorrect" << std::endl; return (0);}
                break;
            case 2:
                if (!checkDay(token)){ std::cout << "Error: Day value is incorrect" << std::endl; return (0);}
                break;
            default:
                return (0);
        }
        token = std::strtok(NULL, "-");
        counter++;
    }
    return (1);
}

int validateValues(std::map<std::string, std::string> &uMap, bool isInputData) {
    std::string value;
    std::map<std::string, std::string>::iterator it;
    it = uMap.begin();
    // std::cout << "last :" << it->second << std::endl;
    double dayVal;
    char *ptr;

    value = strTrim(const_cast<char *>(it->second.c_str()));
    dayVal = std::strtod(value.c_str(), &ptr);
    if(*ptr != '\0')
    {
        std::cout << "Error: Value is incorrect" << std::endl;
        return (0);
    }
    if(isInputData && (dayVal < 0 || dayVal > 1000))
    {
        std::cout << "Error: Value is too large or too small" << std::endl;
        return (0);
    }
    return (1);
}

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

void populateFInputMap(std::string date, std::string value, std::map<s_date, double> &fInputMap) {
    (void)value;
    int counter = 0;
    std::istringstream iss(date);
    std::string token;
    s_date dt;
    while (std::getline(iss, token, '-'))
    {
        switch (counter) {
            case 0:
                dt.year = populateYear(token);
                break ;
            case 1:
                dt.month = populateYear(token);
                break;
            case 2:
                dt.day = populateYear(token);
                break;
        }
        counter++;
    }
    fInputMap[dt] = pulateValue(value);
}

void parseInput(std::string line, std::map<s_date, double> &fMap, char sep) {
    std::map<std::string, std::string>uMap;
    parseSingleLine(uMap, line, sep);
    std::map<std::string, std::string>::iterator it;
    for (it = uMap.begin();  it != uMap.end(); it++)
    {
        if(validateData(uMap) && validateDate(uMap) && validateValues(uMap, sep == '|' ? 1 : 0))
        {
            populateFInputMap(it->first, it->second, fMap);
            // std::cout << "key: " << it->first << " | value: " << it->second << std::endl;
        }
    }
}

int parseFirstLine(std::string str, const char *val1, const char *val2, char sep) {
    (void)sep;
    int counter = 0;
    std::istringstream iss(str);
    std::string token;
    while(std::getline(iss, token, sep)) {
        switch (counter) {
            case 0:
                if (strcmp(strTrim(const_cast<char *>(token.c_str())).c_str(), val1)) return (0);
                break;
            case 1:
                if (strcmp(strTrim(const_cast<char *>(token.c_str())).c_str(), val2)) return (0);
                break;
            default:
                return (0);
        }
        counter++;
    }
    return (1);
}

int main(int argc, char **argv)
{
    (void)argv;
    std::map<s_date, double>fInputMap;
    std::map<s_date, double>fDataMap;

    if(argc != 2) {
        std::cout << "Error: could not open file." << std::endl;
        return (1);
    }
    //MAKE SURE THIS CHANGES TO argv[1]
    std::ifstream inputFile("input.txt");
    if(!inputFile.is_open())
    {
        std::cout << "Error: could not open file." << std::endl;
        return (1);
    }
    std::string line;
    int firstLine = 1;
    while (std::getline(inputFile, line)) {
        if(firstLine) {
            firstLine = 0;
            if(!parseFirstLine(line, "date", "value", '|')) {
                std::cout << "failed first line\n";
                return (1);
            }
        }
        else {
            parseInput(line, fInputMap, '|');
        }
    }
    std::cout << "-------------------------\n";
    std::map<s_date, double>::iterator it;
    for (it = fInputMap.begin();  it != fInputMap.end(); it++)
    {
            std::cout << "key: " << it->first.year << "-" << it->first.month << "-" << it->first.day << " | value: " << it->second << std::endl;
    }
    std::cout << "-------------------------\n";
    std::ifstream dataFile("data.csv");
    if(!dataFile.is_open())
    {
        std::cout << "Error: could not open file." << std::endl;
        return (1);
    }
    firstLine = 1;
    std::string dataLine;
    while (std::getline(dataFile, dataLine)) {
        if(firstLine) {
            firstLine = 0;
            if(!parseFirstLine(dataLine, "date", "exchange_rate", ',')) {
                std::cout << "failed first line\n";
                return (1);
            }
        }
        else {
            parseInput(dataLine, fDataMap, ',');
        }
    }
    for (it = fDataMap.begin();  it != fDataMap.end(); it++)
    {
            std::cout << "key: " << it->first.year << "-" << it->first.month << "-" << it->first.day << ",value: " << it->second << std::endl;
    }
    return (0);
}