#include <iostream>
#include <list>
#include "PmergeMe.hpp"

struct l_struct g_struct;

// Function to insert an element at the correct position in the list
void insert(std::list<std::pair<int, int> >& myList, std::list<std::pair<int, int> >::iterator itr) {
    if (itr == myList.begin()) {
        return;
    }

    std::list<std::pair<int, int> >::iterator prev = itr;
    --prev;

    if (itr->second < prev->second) {
        std::swap(*itr, *prev);
        insert(myList, prev);
    }
}

//  Recursive Insertion Sort function
void recursiveInsertionSort(std::list<std::pair<int, int> >& myList, std::list<std::pair<int, int> >::iterator current) {
    if (current == myList.begin()) {
        return;  // Base case: If we have reached the beginning of the list, we are done.
    }

    std::list<std::pair<int, int> >::iterator prev = current;
    --prev;

    // Sort the rest of the list recursively
    recursiveInsertionSort(myList, prev);

    // Insert the current element at the correct position
    insert(myList, current);
}

void populateMainAndPendList(void) {
    std::list<std::pair<int, int> >::iterator it;
    it = g_struct.pairVec.begin();
    for (; it != g_struct.pairVec.end(); ++it) {
        g_struct.pend.push_back(it->first);
        g_struct.main.push_back(it->second);
    }
}

void sortListPairs() {
    std::list<std::pair<int, int> >::iterator it;
    int temp;
    for (it = g_struct.pairVec.begin(); it != g_struct.pairVec.end(); ++it) {
        if(it->first > it->second)
        {
            temp = it->first;
            it->first = it->second;
            it->second = temp; 
        }
    }
}

void mergeInsertSort(void) {
    std::list <int>::iterator pendIt = g_struct.pend.begin();
    std::list <int>::iterator tmpStop;
    std::list <int>::iterator itUpperBound;
    std::list <int>::iterator itStop = g_struct.main.begin();

    for (size_t i = 0; i < g_struct.pend.size(); i++)
    {
        itUpperBound = std::upper_bound(g_struct.main.begin(), g_struct.main.end(), *pendIt);
        g_struct.main.insert(itUpperBound, *pendIt);
        std::advance(pendIt, 1);
    }
}

int main() {
    g_struct.pairVec.push_back(std::make_pair(7, 0));
    // g_struct.pairVec.push_back(std::make_pair(3, 1));
    // g_struct.pairVec.push_back(std::make_pair(8, 4));
    // g_struct.pairVec.push_back(std::make_pair(6, 0));
    // g_struct.pairVec.push_back(std::make_pair(10, 5));
    
    std::cout << "Original List:" << std::endl;
    std::list<std::pair<int, int> >::iterator it;
    for (it = g_struct.pairVec.begin(); it != g_struct.pairVec.end(); ++it) {
        std::cout << "(" << it->first << ", " << it->second << ") ";
    }
    sortListPairs();
    recursiveInsertionSort(g_struct.pairVec, std::prev(g_struct.pairVec.end()));
    std::cout << "\nSorted List based on the second element (with tie-breaker on first element):" << std::endl;
    for (it = g_struct.pairVec.begin(); it != g_struct.pairVec.end(); ++it) {
        std::cout << "(" << it->first << ", " << it->second << ") ";
    }
    std::cout << "\n";
    populateMainAndPendList();
    mergeInsertSort();
    std::list<int>::iterator lIt;
    for (lIt = g_struct.main.begin(); lIt != g_struct.main.end(); ++lIt) {
        std::cout << "(" << *lIt << ") ";
    }
    return 0;
}
