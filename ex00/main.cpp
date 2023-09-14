#include "BitcoinExchange.hpp"

std::map<std::string, double>fDataMap;


int main(int argc, char **argv)
{
    (void)argv;
    int counter = 0;
    std::map<std::string, double>fInputMap;
    std::map<std::string, double>::iterator it;
    if(argc != 2) {
        std::cout << "Error: could not open file." << std::endl;
        return (1);
    }
    int firstLine = 1;
    std::ifstream dataFile("data.csv");
    if(!dataFile.is_open())
    {
        std::cout << "Error: could not open file." << std::endl;
        return (1);
    }
    std::string dataLine;
    while (std::getline(dataFile, dataLine)) {
        counter++;
        if(firstLine) {
            firstLine = 0;
            if(!parseFirstLine(dataLine, "date", "exchange_rate", ',')) {
                std::cout << "failed first line\n";
                return (1);
            }
        }
        else {
            if(!parseInput(dataLine, fDataMap, ','))
            {
                std::cout << "Error in data.csv \n";
                return (1);
            }                   
        }
    }
    if(counter < 2)
    {
        std::cout << "Please provide meaningful data inside data.csv" << std::endl;
        return (1);
    }
    // //MAKE SURE THIS CHANGES TO argv[1]
    std::ifstream inputFile(argv[1]);
    if(!inputFile.is_open())
    {
        std::cout << "Error: could not open file." << std::endl;
        return (1);
    }
    std::string line;
    counter = 0;
    firstLine = 1;
    while (std::getline(inputFile, line)) {
        counter++;
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
    if(counter < 2)
    {
        std::cout << "Please provide meaningful data inside " << argv[1] << std::endl;
        return (1);
    }

    return (0);
}
/*
    2011-01-03 => 3 = 0.9
    2011-01-03 => 2 = 0.6
    2011-01-03 => 1 = 0.3
    2011-01-03 => 1.2 = 0.36
    2011-01-09 => 1 = 0.32
    Error: not a positive number.
    Error: bad input => 2001-42-42
    2012-01-11 => 1 = 7.1
    Error: too large a number
*/