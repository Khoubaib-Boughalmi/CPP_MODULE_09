#include "BitcoinExchange.hpp"

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
    {
        std::cout << "Error: Date format is incorrect" << std::endl;
        return (0);
    }
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
        }
        token = std::strtok(NULL, "-");
        counter++;
    }
    if(counter != 3)
    { std::cout << "Error: Date format is incorrect" << std::endl; return (0);}
    return (1);
}

int validateValues(std::map<std::string, std::string> &uMap, bool isInputData) {
    std::string value;
    std::map<std::string, std::string>::iterator it;
    it = uMap.begin();
    // std::cout << "last :" << it->second << std::endl;
    double dVal;
    char *ptr;

    value = strTrim(const_cast<char *>(it->second.c_str()));

    if(value.length() == 0)
    {
        std::cout << "Error: No value provided" << std::endl;
        return (0);
    }
    dVal = std::strtod(value.c_str(), &ptr);
    if(*ptr != '\0')
    {
        std::cout << "Error: Value is incorrect" << std::endl;
        return (0);
    }
    if(isInputData && (dVal < 0 || dVal > 1000))
    {
        std::cout << "Error: Value is too large or too small" << std::endl;
        return (0);
    }
    return (1);
}


int parseInput(std::string line, std::map<std::string, double> &fMap, char sep) {
    int counter  = 0;
    std::map<std::string, std::string>uMap;
    parseSingleLine(uMap, line, sep);
    std::map<std::string, std::string>::iterator it;
    for (it = uMap.begin();  it != uMap.end(); it++)
    {
        if(validateData(uMap) && validateDate(uMap) && validateValues(uMap, sep == '|' ? 1 : 0))
        {
            populateFInputMap(it->first, it->second, fMap, sep == '|' ? 1 : 0);
            counter++;
        }
    }
    if(sep == ',' && !counter)
        return (0);
    return (1);
}

int parseFirstLine(std::string str, const char *val1, const char *val2, char sep) {
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
        }
        counter++;
    }
    if(!counter)
        return (0);
    return (1);
}
