#include "RPN.h"

std::stack<int> rpnStack;

int isOperator(char c) {
    if(c == '+' || c == '-' || c == '*' || c == '/')
        return (1);
    return (0);
}

int isValidInput(char c)
{
    if(c == ' ' || c == '\t' || isOperator(c) || isdigit(c))
        return (1);
    return (0);
}

int parseInput(char *input) {
    size_t i = 0;

    while (input[i] && isValidInput(input[i])) {i++;}
    if(input[i])
        return (0);
    return (1);
}

void doCalculation(char op) {
    int firstNumber;
    int secondNumber;
    int resNumber;

    if(rpnStack.size() < 2)
    {
        std::cout << "Error" << std::endl;
        exit(1);
    }
    firstNumber = rpnStack.top();
    rpnStack.pop();
    secondNumber = rpnStack.top();
    rpnStack.pop();
    switch(op) {
        case '+':
        resNumber = secondNumber + firstNumber;
        break;
        case '-':
        resNumber = secondNumber - firstNumber;
        break;
        case '*':
        resNumber = secondNumber * firstNumber;
        break;
        case '/': // check for 0 division
        if(firstNumber != 0)
            resNumber = secondNumber / firstNumber;
        else
        {
            std::cout << "division by 0" << std::endl;
            exit(1);
        }
        break;
    }
    rpnStack.push(resNumber);
}

void doTheMagic(char *input) {
    size_t i = 0;
    while (input[i])
    {
        while (input[i] && (input[i] == ' ' || input[i] == '\t'))
            i++;
        if(isdigit(input[i]))
        {
            rpnStack.push(std::strtol(input + i, NULL, 10));
            i++;
        }
        else if(isOperator(input[i]))
        {
            doCalculation(input[i]);
            i++;
        }
    }
}

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