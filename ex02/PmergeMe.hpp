#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <list>
#include <utility>
#include <cstdio>
#include <climits>
#include <algorithm>
#include <iostream>

struct v_struct {
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
    std::list<int> initialInputList;
    std::list< std::pair<int, int> > pairList;
    std::list <int> main;
    std::list <int>::iterator *itArr; // MAKE SURE TO FREE THIS AT THE END
    std::list <int> pend;
};
extern struct v_struct g_vec_struct;
extern struct l_struct g_list_struct;

int validateInput(char *input);
int parseInput(char *input);
/*-------List----------*/
void mergeInsertSort_list(void);
void sortPairs_list();
void populateMainAndPend_list(void);
void recursiveInsertionSort_list(std::list<std::pair<int, int> >& myList, std::list<std::pair<int, int> >::iterator current);
void insert_list(std::list<std::pair<int, int> >& myList, std::list<std::pair<int, int> >::iterator itr);
void populatePair_list(void);
void displayPairs_list(void);
/*-------Vec----------*/
void mergeInsertSortVec(void);
void mergeInsertSortFirstTwoElements(void);
void mergeinsert(void);
void populateMainAndPendVec(void);
void displayPairs_vec(void);
void insertionSort(std::vector<int> &vecArr);
void recursiveInsertionSortVec(std::vector< std::pair<int, int> > &vecArr, unsigned int n);
void sortVecPairs(std::vector< std::pair<int, int> >::iterator it, std::vector< std::pair<int, int> >::iterator end);
void populatePairVec(void);
int jacobsthal(int n);


#endif