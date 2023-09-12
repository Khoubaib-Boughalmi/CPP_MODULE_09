#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <list>
#include <utility>
#include <cstdio>
#include <climits>
#include <algorithm>
#include <iostream>

struct s_struct {
    int size;
    int stranggler;
    std::vector<int> initialInputVec;
    std::vector< std::pair<int, int> > pairVec;
    std::vector <int> main;
    std::vector <int>::iterator *itArr; // MAKE SURE TO FREE THIS AT THE END
    std::vector <int> pend;
};

struct l_struct {
    int size;
    int stranggler;
    std::list<int> initialInputVec;
    std::list< std::pair<int, int> > pairVec;
    std::list <int> main;
    std::list <int>::iterator *itArr; // MAKE SURE TO FREE THIS AT THE END
    std::list <int> pend;
};
#endif