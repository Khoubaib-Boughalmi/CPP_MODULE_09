#include "PmergeMe.hpp"

int jacobsthal(int n) {
    if (n == 0)
        return 0;
    else if (n == 1)
        return 1;
    else
        return jacobsthal(n - 1) + 2 * jacobsthal(n - 2);
}

void populatePairVec(void) {
    if(g_struct.initialInputVec.size() % 2)
    {
        g_struct.stranggler = g_struct.initialInputVec[g_struct.initialInputVec.size() - 1];
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

void recursiveInsertionSort(std::vector< std::pair<int, int> > &vecArr, unsigned int n) {
    if(n <= 1)
        return ;
    recursiveInsertionSort(vecArr, n - 1);
    std::pair<int, int> lastEelement = vecArr[n - 1];
    int j = n - 2;
    while(j >= 0 && vecArr[j].second > lastEelement.second) {
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

void populateMainAndPendVec(void) {
    for (size_t i = 0; i < g_struct.pairVec.size(); i++) //i think i should check for odd pairs not sure
    {
        g_struct.pend.push_back(g_struct.pairVec[i].first);
        g_struct.main.push_back(g_struct.pairVec[i].second);
    }
}

void mergeinsert(void) {
    std::vector <int>::iterator it;
    for (size_t i = 0; i < g_struct.pend.size(); i++)
    {
        it = std::upper_bound(g_struct.main.begin(), g_struct.main.end(), g_struct.pend[i]);
        if(it == g_struct.main.begin())
            g_struct.main.insert(g_struct.main.begin(), g_struct.pend[i]);
        else
            g_struct.main.insert(it, g_struct.pend[i]);
    }
}

void mergeInsertSortFirstTwoElements() {
    std::vector <int>::iterator itStart;
    std::vector <int>::iterator itEnd;
    std::vector <int>::iterator it;
    //insert first pend in main
    g_struct.main.insert(g_struct.main.begin(), g_struct.pend[0]);
    // insert second pend in main
    itStart = g_struct.main.begin();
    itEnd = itStart;
    std::advance(itEnd, 2);
    it = std::upper_bound(itStart, itEnd, g_struct.pend[1]);
    g_struct.main.insert(it, g_struct.pend[1]);
}

void mergeInsertSort(void) {
    std::vector <int>::iterator itUpperBound;
    std::vector <int>::iterator tmpStop;
    std::vector <int>::iterator itStop = g_struct.main.begin();
    // int currentJSIndex = 3;
    std::advance(itStop, 4);
    mergeInsertSortFirstTwoElements();
    for (size_t i = 2; i < g_struct.pend.size(); i++)
    {
        itUpperBound = std::upper_bound(g_struct.main.begin(), g_struct.main.end(), g_struct.pend[i]);
        g_struct.main.insert(itUpperBound, g_struct.pend[i]);
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
        return (0);
    populatePairVec();
    std::vector< std::pair<int, int> >::iterator pairVecIterator;
    std::vector< std::pair<int, int> >::iterator pairVecEndIterator;
    pairVecIterator = g_struct.pairVec.begin();
    pairVecEndIterator = g_struct.pairVec.end();
    sortPairs(pairVecIterator, pairVecEndIterator);
    recursiveInsertionSort(g_struct.pairVec, g_struct.pairVec.size());
    populateMainAndPendVec();
    displayPairs();
    std::cout << "--------------------\n";
    mergeInsertSort();
    for (size_t i = 0; i < g_struct.main.size(); i++)
        std::cout << g_struct.main[i] << " ";
    return (0);
}