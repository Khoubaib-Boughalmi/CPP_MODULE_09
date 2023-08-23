#include "BitcoinExchange.h"

//!!!!!!!!!! RETURN OF STRTRIM SHOULD BE FREED
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

void parseSingleLine(std::map<std::string, std::string> &uMap, std::string line) {
    char *token = NULL;
    char *key = const_cast<char*>("");
    char *value = const_cast<char*>("");
    int setErr = 0;
    if(checkNumberOccurrences(line, '|') > 1)
        setErr = 1;
    if(!strcmp(strTrim(const_cast<char *>(line.c_str())).c_str(), "|"))
        setErr = 1;
    if(strTrim(const_cast<char *>(line.c_str()))[0] == '|')
        setErr = 1;
    if(!setErr)
    {
        token = std::strtok(const_cast<char *>(line.c_str()), "|");
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
    (void)uMap;
    std::map<std::string, std::string>::iterator it;
    it = uMap.begin();
    if(!it->first[0] || !it->second[0])
        return (0);
    return (1);
}

int checkYear(char *year) {
    long yearVal;
    char *ptr;

    yearVal = std::strtol(year, &ptr, 10);
    // if(*ptr != '-')
    //     return (0);
    std::cout << "UearVal: " << yearVal << std::endl;
    return (1);
}
int checkMonth(char *year) {(void) year; return (1);}
int checkDay(char *year) {(void) year; return (1);}

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
                if (!checkYear(token)) return (0);
                break ;
            case 1:
                if (!checkMonth(token)) return (0);
                break;
            case 2:
                if (!checkDay(token)) return (0);
                break;
            default:
                return (0);
        }
        std::cout << token << " " ;
        token = std::strtok(NULL, "-");
        counter++;
    }
    std::cout << std::endl;
    return (1);
}

int validateValues(std::map<std::string, std::string> &uMap) {
    (void)uMap;
    // std::map<std::string, std::string>::iterator it;
    // if(!it->first[0] || !it->second[0])
    //     return (0);
    return (1);
}

void parseInput(std::string line) {
    std::map<std::string, std::string>uMap;
    parseSingleLine(uMap, line);
    std::map<std::string, std::string>::iterator it;
    for (it = uMap.begin();  it != uMap.end(); it++)
    {
        if(validateData(uMap) && validateDate(uMap) && validateValues(uMap)) {}
            // std::cout << "key: " << it->first << " | value: " << it->second << std::endl;
        // else
            // std::cout << "Error with input data" << std::endl;

    }
    
}

int parseFirstLine(std::string str) {
    int counter = 0;
    char *token = std::strtok(const_cast<char *>(str.c_str()), "|");
    while(token) {
        switch (counter) {
            case 0:
                if (strcmp(strTrim(token).c_str(), "date")) return (0);
                break;
            case 1:
                if (strcmp(strTrim(token).c_str(), "value")) return (0);
                break;
            default:
                return (0);
        }
        token = std::strtok(NULL, "|");
        counter++;
    }
    return (1);
}

int main(int argc, char **argv)
{
    (void)argv;
    if(argc != 2) {
        std::cout << "Error: could not open file." << std::endl;
        return (1);
    }
    std::ifstream inputFile("input.txt");
    if(!inputFile.is_open())
        return (1);
    std::string line;
    int firstLine = 1;
    while (std::getline(inputFile, line)) {
        if(firstLine) {
            firstLine = 0;
            if(!parseFirstLine(line)) {
                std::cout << "failed first line\n";
                return (1);
            }
        }
        else {
            parseInput(line);
        }
    }
    
    return (0);
}