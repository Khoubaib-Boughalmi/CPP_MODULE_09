#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <utility>
#include <cstdio>
#include <climits>
#include <algorithm>
#include <iostream>

struct s_struct {
    int size;
    int straggler;
    std::vector<int> initialInputVec;
    std::vector< std::pair<int, int> > pairVec;
    std::vector <int> main;
    std::vector <int> pend;
};
#endif