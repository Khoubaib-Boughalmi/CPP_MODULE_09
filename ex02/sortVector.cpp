#include "PmergeMe.hpp"

int jacobsthal(int n) {
    if (n == 0)
        return 0;
    else if (n == 1)
        return 1;
    else
        return jacobsthal(n - 1) + 2 * jacobsthal(n - 2);
}

void populatePair_vec(void) {
    if(g_vec_struct.initialInputVec.size() % 2)
    {
        g_vec_struct.stranggler = g_vec_struct.initialInputVec[g_vec_struct.initialInputVec.size() - 1];
        g_vec_struct.initialInputVec.pop_back();
    }
    for (size_t i = 0; i < g_vec_struct.initialInputVec.size(); i+=2)
        g_vec_struct.pairVec.push_back(std::make_pair(g_vec_struct.initialInputVec[i], g_vec_struct.initialInputVec[i+1]));       
}

void sortPairs_vec(std::vector< std::pair<int, int> >::iterator it, std::vector< std::pair<int, int> >::iterator end) {
    int tmp;
    if(it == end)
        return ;
    if(it->first > it->second)
    {
        tmp = it->first;
        it->first = it->second;
        it->second = tmp;
    }
    sortPairs_vec(++it, end);
}

void recursiveInsertionSort_vec(std::vector< std::pair<int, int> > &vecArr, unsigned int n) {
    if(n <= 1)
        return ;
    recursiveInsertionSort_vec(vecArr, n - 1);
    std::pair<int, int> lastEelement = vecArr[n - 1];
    int j = n - 2;
    while(j >= 0 && vecArr[j].second > lastEelement.second) {
        vecArr[j + 1] = vecArr[j];
        j--;
    }
    vecArr[j + 1] = lastEelement;
}

void insertionSort_vec(std::vector<int> &vecArr) {
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

void displayPairs_vec() {
    for (size_t i = 0; i < g_vec_struct.pairVec.size(); i++)
    {
        std::cout << g_vec_struct.pairVec[i].first << " " << g_vec_struct.pairVec[i].second << std::endl; 
    }
}

void populateMainAndPend_vec(void) {
    for (size_t i = 0; i < g_vec_struct.pairVec.size(); i++) //i think i should check for odd pairs not sure
    {
        g_vec_struct.pend.push_back(g_vec_struct.pairVec[i].first);
        g_vec_struct.main.push_back(g_vec_struct.pairVec[i].second);
    }
}

void mergeinsert(void) {
    std::vector <int>::iterator it;
    for (size_t i = 0; i < g_vec_struct.pend.size(); i++)
    {
        it = std::upper_bound(g_vec_struct.main.begin(), g_vec_struct.main.end(), g_vec_struct.pend[i]);
        if(it == g_vec_struct.main.begin())
            g_vec_struct.main.insert(g_vec_struct.main.begin(), g_vec_struct.pend[i]);
        else
            g_vec_struct.main.insert(it, g_vec_struct.pend[i]);
    }
}

void mergeInsertSortFirstTwoElements_vec() {
    std::vector <int>::iterator itStart;
    std::vector <int>::iterator itEnd;
    std::vector <int>::iterator it;
    //insert first pend in main
    g_vec_struct.main.insert(g_vec_struct.main.begin(), g_vec_struct.pend[0]);
    // insert second pend in main
    itStart = g_vec_struct.main.begin();
    itEnd = itStart;
    std::advance(itEnd, 2);
    it = std::upper_bound(itStart, itEnd, g_vec_struct.pend[1]);
    g_vec_struct.main.insert(it, g_vec_struct.pend[1]);
}

void mergeInsertSort_vec(void) {
    std::vector <int>::iterator itUpperBound;
    std::vector <int>::iterator tmpStop;
    std::vector <int>::iterator itStop = g_vec_struct.main.begin();
    if(g_vec_struct.initialInputVec.size() > 2)
    {
        std::advance(itStop, 4);
        mergeInsertSortFirstTwoElements_vec();
        for (size_t i = 2; i < g_vec_struct.pend.size(); i++)
        {
            itUpperBound = std::upper_bound(g_vec_struct.main.begin(), g_vec_struct.main.end(), g_vec_struct.pend[i]);
            g_vec_struct.main.insert(itUpperBound, g_vec_struct.pend[i]);
        }
    }
    else
    {
        for (size_t i = 0; i < g_vec_struct.pend.size(); i++)
        {
            itUpperBound = std::upper_bound(g_vec_struct.main.begin(), g_vec_struct.main.end(), g_vec_struct.pend[i]);
            g_vec_struct.main.insert(itUpperBound, g_vec_struct.pend[i]);
        }

    }
}

void insertStranggler_vec() {
    if(g_vec_struct.stranggler >= 0)
    {
        std::vector<int>::iterator it;
        it = std::upper_bound(g_vec_struct.main.begin(), g_vec_struct.main.end(), g_vec_struct.stranggler);
        g_vec_struct.main.insert(it, g_vec_struct.stranggler);
    }
}