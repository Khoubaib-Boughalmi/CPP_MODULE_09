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

int parseFirstLine(std::string str)
{
    int counter = 0;
    char *token = std::strtok(const_cast<char *>(str.c_str()), "|");
    while(token)
    {
        switch (counter)
        {
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
    if(argc != 2)
    {
        std::cout << "Error: could not open file." << std::endl;
        return (1);
    }
    // std::string str = " hello   | sadsad |123|||a";
    // char *token = std::strtok(const_cast<char *>(str.c_str()), "|");
    // while(token)
    // {
    //     std::cout << strTrim(token) << std::endl;
    //     token = std::strtok(NULL, "|");
    // }
    std::ifstream inputFile("input.txt");
    if(!inputFile.is_open())
        return (1);
    std::string line;
    int firstLine = 1;
    while (std::getline(inputFile, line))
    {
        if(firstLine)
        {
            firstLine = 0;
            if(!parseFirstLine(line))
            {
                std::cout << "failed first line\n";
                return (1);
            }
        }
    }
    
    return (0);
}