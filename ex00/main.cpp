#include "BitcoinExchange.h"

std::string strTrim(char * passedStr) {
    size_t start;
    size_t end;

    std::string str(passedStr);
    start = str.find_first_not_of(" \t\r"); 
    if(start == std::string::npos)
        return "";
    end = str.find_last_not_of(" \t\r"); 
    return str.substr(start, end - start + 1);
}

int main(int argc, char **argv)
{
    (void)argv;
    if(argc != 2)
    {
        std::cout << "Error: could not open file." << std::endl;
        return (1);
    }
    std::string str = " hello    sadsad |123";
    char *token = std::strtok(const_cast<char *>(str.c_str()), "|");
    while(token)
    {
        std::cout << strTrim(token) << std::endl;
        token = std::strtok(NULL, "|");
    }
    return (0);
}