#include "PmergeMe.hpp"

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
    if (current == myList.begin())
        return;

    std::list<std::pair<int, int> >::iterator prev = current;
    --prev;
    recursiveInsertionSort_list(myList, prev);
    insert_list(myList, current);
}

void populateMainAndPend_list(void) {
    std::list<std::pair<int, int> >::iterator it;
    it = g_list_struct.pairList.begin();
    for (; it != g_list_struct.pairList.end(); ++it) {
        g_list_struct.pend.push_back(it->first);
        g_list_struct.main.push_back(it->second);
    }
}

void populatePair_list() {
    if(g_list_struct.initialInputList.size() % 2)
    {
        g_list_struct.stranggler = *(g_list_struct.initialInputList.end()--);
        g_list_struct.initialInputList.pop_back();
    }
    std::list< int >::iterator it = g_list_struct.initialInputList.begin();
    for (; it != g_list_struct.initialInputList.end(); it++)
        g_list_struct.pairList.push_back(std::make_pair(*it, *(it++)));       
}

void sortPairs_list() {
    std::list<std::pair<int, int> >::iterator it;
    int temp;
    for (it = g_list_struct.pairList.begin(); it != g_list_struct.pairList.end(); ++it) {
        if(it->first > it->second)
        {
            temp = it->first;
            it->first = it->second;
            it->second = temp; 
        }
    }
}

void displayPairs_list(void) {
    std::cout << "Pair List:"; 
    std::list<std::pair< int, int> >::iterator pairIt = g_list_struct.pairList.begin();
    for (; pairIt != g_list_struct.pairList.end(); pairIt++)
    {
        std::cout << "(" << pairIt->first << " " <<  pairIt->second << ") ";
    }
}

void mergeInsertSort_list(void) {
    std::list <int>::iterator pendIt = g_list_struct.pend.begin();
    std::list <int>::iterator tmpStop;
    std::list <int>::iterator itUpperBound;

    for (size_t i = 0; i < g_list_struct.pend.size(); i++)
    {
        itUpperBound = std::upper_bound(g_list_struct.main.begin(), g_list_struct.main.end(), *pendIt);
        g_list_struct.main.insert(itUpperBound, *pendIt);
        std::advance(pendIt, 1);
    }
}

// int main() {
//     g_list_struct.pairList.push_back(std::make_pair(7, 0));
//     // g_list_struct.pairList.push_back(std::make_pair(3, 1));
//     // g_list_struct.pairList.push_back(std::make_pair(8, 4));
//     // g_list_struct.pairList.push_back(std::make_pair(6, 0));
//     // g_list_struct.pairList.push_back(std::make_pair(10, 5));
    
//     std::cout << "Original List:" << std::endl;
//     std::list<std::pair<int, int> >::iterator it;
//     for (it = g_list_struct.pairList.begin(); it != g_list_struct.pairList.end(); ++it) {
//         std::cout << "(" << it->first << ", " << it->second << ") ";
//     }
//     sortListPairs();
//     recursiveInsertionSort(g_list_struct.pairList, g_list_struct.pairList.end()--);
//     std::cout << "\nSorted List based on the second element (with tie-breaker on first element):" << std::endl;
//     for (it = g_list_struct.pairList.begin(); it != g_list_struct.pairList.end(); ++it) {
//         std::cout << "(" << it->first << ", " << it->second << ") ";
//     }
//     std::cout << "\n";
//     populateMainAndPendList();
//     mergeInsertSort();
//     std::list<int>::iterator lIt;
//     for (lIt = g_list_struct.main.begin(); lIt != g_list_struct.main.end(); ++lIt) {
//         std::cout << "(" << *lIt << ") ";
//     }
//     return 0;
// }
