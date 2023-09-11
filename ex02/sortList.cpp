#include <iostream>
#include <list>
#include "PmergeMe.hpp"

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

// Recursive Insertion Sort function
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

int main() {
    std::list<std::pair<int, int> > myList;
    myList.push_back(std::make_pair(3, 1));
    myList.push_back(std::make_pair(1, 4));
    myList.push_back(std::make_pair(4, 5));
    myList.push_back(std::make_pair(2, 0));
    
    std::cout << "Original List:" << std::endl;
    std::list<std::pair<int, int> >::iterator it;
    for (it = myList.begin(); it != myList.end(); ++it) {
        std::cout << "(" << it->first << ", " << it->second << ") ";
    }
    
    
    recursiveInsertionSort(myList, std::prev(myList.end()));
       
    std::cout << "\nSorted List based on the second element (with tie-breaker on first element):" << std::endl;
    for (it = myList.begin(); it != myList.end(); ++it) {
        std::cout << "(" << it->first << ", " << it->second << ") ";
    }


    return 0;
}
