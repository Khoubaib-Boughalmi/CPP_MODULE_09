#include "RPN.hpp"

std::stack<int> rpnStack;

int main(int argc, char **argv)
{
    if(argc != 2)
    {
        std::cout << "Wrong input please provide" << std::endl;
        return (1);
    }

    if(!parseInput(argv[1]))
    {
        std::cout << "Error" << std::endl;
        return (1);
    }
    doTheMagic(argv[1]);
    if(rpnStack.size() != 1)
    {
        std::cout << "Error" << std::endl;
        return (1);
    }
    std::cout << "Result: " <<  rpnStack.top() << std::endl;
    return (0);
}