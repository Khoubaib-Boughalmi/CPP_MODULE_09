#include "PmergeMe.hpp"

struct s_struct g_struct;

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

    g_struct.size = 0;
    while (*input) {
        while (*input == ' ' || *input == '\t') 
            input++;
        if(*input && isdigit(*input)) {
            g_struct.size++;
            strVal = "";
            while (*input != '\0' && isdigit(*input)) {
                strVal += *input;
                input++;
            }
            val = strtol(strVal.c_str(), NULL, 10);
            if(val > INT_MAX)
                return (0);
            g_struct.initialInputVec.push_back(val);
        }
    }
    return (1);
}

void populatePairVec(void) {
    if(g_struct.initialInputVec.size() % 2)
    {
        g_struct.straggler = g_struct.initialInputVec[g_struct.initialInputVec.size() - 1];
        g_struct.initialInputVec.pop_back();
    }
    for (size_t i = 0; i < g_struct.initialInputVec.size(); i+=2)
        g_struct.pairVec.push_back(std::make_pair(g_struct.initialInputVec[i], g_struct.initialInputVec[i+1]));       
}

void sortPairs(std::vector< std::pair<int, int> >::iterator it, std::vector< std::pair<int, int> >::iterator end) {
    int tmp;
    if(it == end)
        return ;
    if(it->first > it->second)
    {
        tmp = it->first;
        it->first = it->second;
        it->second = tmp;
    }
    sortPairs(++it, end);
}

void recursiveInsertionSort(std::vector<int> &vecArr, int n) {
    if(n <= 1)
        return ;
    recursiveInsertionSort(vecArr, n - 1);
    int lastEelement = vecArr[n - 1];
    int j = n - 2;
    while(j >= 0 && vecArr[j] > lastEelement) {
        vecArr[j + 1] = vecArr[j];
        j--;
    }
    vecArr[j + 1] = lastEelement;
}

void insertionSort(std::vector<int> &vecArr) {
    size_t i = 1;
    size_t hole = 0;
    int tmp;
    while (i < vecArr.size())
    {
        hole = i;
        tmp = vecArr[i];
        while (i > 0 && tmp < vecArr[i - 1])
        {
            vecArr[i] = vecArr[i - 1];
            i--;
        }
        vecArr[i] = tmp;
        i = hole + 1;
    }
    for (size_t i = 0; i < 10; i++)
       std::cout << vecArr[i] << " ";

}

void displayPairs() {
    for (size_t i = 0; i < g_struct.pairVec.size(); i++)
    {
        std::cout << g_struct.pairVec[i].first << " " << g_struct.pairVec[i].second << std::endl; 
    }
    
}
int main(int argc, char **argv)
{
    if(argc != 2) {
        std::cout << "Problem with input" << std::endl;
        return (1);
    }
    if(!validateInput(argv[1]) || !parseInput(argv[1])) {
        std::cout << "Problem with input" << std::endl;
        return (1);
    }
    if(g_struct.initialInputVec.size() < 2)
        return (0); //display this vec;
    populatePairVec(); // create a vector of pairs
    std::vector< std::pair<int, int> >::iterator pairVecIterator;
    std::vector< std::pair<int, int> >::iterator pairVecEndIterator;
    pairVecIterator = g_struct.pairVec.begin();
    pairVecEndIterator = g_struct.pairVec.end();
    sortPairs(pairVecIterator, pairVecEndIterator);
    displayPairs();


    int intArr[10] = {3, 1, 2, 4, 0, 9, 7, 2, 5, 6};
    std::vector<int>vecArr;
    for (size_t i = 0; i < 10; i++)
        vecArr.push_back(intArr[i]);    

    recursiveInsertionSort(vecArr, 10);
    for (size_t i = 0; i < 10; i++)
        std::cout << vecArr[i] << " ";
    return (0);
}