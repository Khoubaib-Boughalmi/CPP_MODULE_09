#include "PmergeMe.hpp"

int validateInput(char *input) {
    size_t i = 0;
    while (input[i] && (input[i] == ' ' || input[i] == '\t' || isdigit(input[i])))
        i++;
    if(input[i])
        return (0);
    return (1);
}

int parseInput(char *input) {
    long val;
    std::string strVal;

    g_vec_struct.size = 0;
    while (*input) {
        while (*input == ' ' || *input == '\t') 
            input++;
        if(*input && isdigit(*input)) {
            g_vec_struct.size++;
            strVal = "";
            while (*input != '\0' && isdigit(*input)) {
                strVal += *input;
                input++;
            }
            val = strtol(strVal.c_str(), NULL, 10);
            if(val > INT_MAX)
                return (0);
            g_vec_struct.initialInputVec.push_back(val);
        }
    }
    return (1);
}
