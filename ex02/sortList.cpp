#include <iostream>
#include <list>
#include "PmergeMe.hpp"

struct l_struct g_list_struct;

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

    // g_vec_struct.size = 0;
    while (*input) {
        while (*input == ' ' || *input == '\t') 
            input++;
        if(*input && isdigit(*input)) {
            // g_vec_struct.size++;
            strVal = "";
            while (*input != '\0' && isdigit(*input)) {
                strVal += *input;
                input++;
            }
            val = strtol(strVal.c_str(), NULL, 10);
            if(val > INT_MAX)
                return (0);
            // g_vec_struct.initialInputVec.push_back(val);
            g_list_struct.initialInput_list.push_back(val);
        }
    }
    g_list_struct.stranggler = -1;
    g_vec_struct.stranggler = -1;
    return (1);
}

// Function to insert an element at the correct position in the list
void insert_list(std::list<std::pair<int, int> >& myList, std::list<std::pair<int, int> >::iterator itr) {
    if (itr == myList.begin()) {
        return;
    }

    std::list<std::pair<int, int> >::iterator prev = itr;
    --prev;

    if (itr->second < prev->second) {
        std::swap(*itr, *prev);
        insert_list(myList, prev);
    }
}

//  Recursive Insertion Sort function
void recursiveInsertionSort_list(std::list<std::pair<int, int> >& myList, std::list<std::pair<int, int> >::iterator current) {
    if (current == myList.begin()) {
        return;  // Base case: If we have reached the beginning of the list, we are done.
    }

    std::list<std::pair<int, int> >::iterator prev = current;
    --prev;

    // Sort the rest of the list recursively
    recursiveInsertionSort_list(myList, prev);

    // Insert the current element at the correct position
    insert_list(myList, current);
}

void populateMainAndPend_list(void) {
    std::list<std::pair<int, int> >::iterator it;
    it = g_list_struct.pair_list.begin();
    for (; it != g_list_struct.pair_list.end(); ++it) {
        g_list_struct.pend.push_back(it->first);
        g_list_struct.main.push_back(it->second);
    }
}

void sortPairs_list() {
    std::list<std::pair<int, int> >::iterator it;
    int temp;
    for (it = g_list_struct.pair_list.begin(); it != g_list_struct.pair_list.end(); ++it) {
        if(it->first > it->second)
        {
            temp = it->first;
            it->first = it->second;
            it->second = temp; 
        }
    }
}

void mergeInsertSort_list(void) {
    std::list <int>::iterator pendIt = g_list_struct.pend.begin();
    std::list <int>::iterator tmpStop;
    std::list <int>::iterator itUpperBound;
    std::list <int>::iterator itStop = g_list_struct.main.begin();

    for (size_t i = 0; i < g_list_struct.pend.size(); i++)
    {
        itUpperBound = std::upper_bound(g_list_struct.main.begin(), g_list_struct.main.end(), *pendIt);
        g_list_struct.main.insert(itUpperBound, *pendIt);
        std::advance(pendIt, 1);
    }
}

void populatePair_list() {
    if(g_list_struct.initialInput_list.size() % 2)
    {
        g_list_struct.stranggler = *(std::prev(g_list_struct.initialInput_list.end()));
        g_list_struct.initialInput_list.pop_back();
    }
    std::list< int >::iterator it = g_list_struct.initialInput_list.begin();
    for (; it != g_list_struct.initialInput_list.end(); it++)
        g_list_struct.pair_list.push_back(std::make_pair(*it, *(it++)));       
}

void displayPairs_list(void) {
    std::cout << "Pair List:"; 
    std::list<std::pair< int, int> >::iterator pairIt = g_list_struct.pair_list.begin();
    for (; pairIt != g_list_struct.pair_list.end(); pairIt++)
    {
        std::cout << "(" << pairIt->first << " " <<  pairIt->second << ") ";
    }
}

void insertStranggler_list() {
    if(g_list_struct.stranggler >= 0)
    {
        std::list<int>::iterator it;
        it = std::upper_bound(g_list_struct.main.begin(), g_list_struct.main.end(), g_list_struct.stranggler);
        g_list_struct.main.insert(it, g_list_struct.stranggler);
    }
}


int main(int argc, char **argv) {    
    if(argc != 2) {
        std::cout << "Problem with input" << std::endl;
        return (1);
    }
    if(!validateInput(argv[1]) || !parseInput(argv[1])) {
        std::cout << "Problem with input" << std::endl;
        return (1);
    }
    std::list<int>::iterator itTemp = g_list_struct.initialInput_list.begin();
    std::cout << "INITAIL: ";
    for (;itTemp != g_list_struct.initialInput_list.end(); itTemp++)
    {
        std::cout << *itTemp << " ";
    }
    populatePair_list();
    displayPairs_list();
    std::cout << "Original List:" << std::endl;
    std::list<std::pair<int, int> >::iterator it;
    for (it = g_list_struct.pair_list.begin(); it != g_list_struct.pair_list.end(); ++it) {
        std::cout << "(" << it->first << ", " << it->second << ") ";
    }
    sortPairs_list();
    recursiveInsertionSort_list(g_list_struct.pair_list, std::prev(g_list_struct.pair_list.end()));
    std::cout << "\nSorted List based on the second element (with tie-breaker on first element):" << std::endl;
    for (it = g_list_struct.pair_list.begin(); it != g_list_struct.pair_list.end(); ++it) {
        std::cout << "(" << it->first << ", " << it->second << ") ";
    }
    std::cout << "\n";
    populateMainAndPend_list();
    mergeInsertSort_list();
    insertStranggler_list();
    std::list<int>::iterator lIt;
    for (lIt = g_list_struct.main.begin(); lIt != g_list_struct.main.end(); ++lIt) {
        std::cout << "(" << *lIt << ") ";
    }
    return 0;
}
