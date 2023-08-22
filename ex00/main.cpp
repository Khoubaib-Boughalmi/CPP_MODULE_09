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

void parseSingleLine(std::map<std::string, std::string> &uMap, std::string line) {
    // char *date = NULL;
    // char *value = NULL;
    (void)uMap;
    if(!strcmp(strTrim(const_cast<char *>(line.c_str())).c_str(), "|"))
    {
        std::cout << "missing data\n";
        return ;
    }
    if(strTrim(const_cast<char *>(line.c_str()))[0] == '|')
    {
        std::cout << "missing data\n";
        return ;
    }
    char *token = std::strtok(const_cast<char *>(line.c_str()), "|");
    // date = token;

    if(token && token[0])
    {
        if(!strTrim(token)[0])
        {
            std::cout << "first Half Empty\n";
            return ;
        }
        else
            std::cout << token << " | ";
    }
    else if(!token || !token[0] || token[0] == '\n')
    {
        return ;
    }
    std::string str;
    if(!strTrim(token).empty())
    {
        token = std::strtok(NULL, "|");
        if(token)
            std::cout << token << std::endl;
        else
            std::cout << "NULL" << std::endl;
    }
}

void parseInput(std::string line) {
    std::map<std::string, std::string>uMap;
    parseSingleLine(uMap, line);
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