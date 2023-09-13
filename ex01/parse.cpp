#include "RPN.hpp"

int isValidInput(char c) {
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