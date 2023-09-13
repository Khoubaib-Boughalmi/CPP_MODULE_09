#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <list>
#include <utility>
#include <cstdio>
#include <climits>
#include <algorithm>
#include <iostream>
#include <ctime>

struct s_struct {
    int size;
    int stranggler;
    std::vector<int> initialInputVec;
    std::vector< std::pair<int, int> > pairVec;
    std::vector <int> main;
    std::vector <int>::iterator *itArr; // MAKE SURE TO FREE THIS AT THE END
    std::vector <int> pend;
};

extern struct s_struct g_vec_struct;
extern struct l_struct g_list_struct;

struct l_struct {
    int size;
    int stranggler;
    std::list<int> initialInput_list;
    std::list< std::pair<int, int> > pair_list;
    std::list <int> main;
    std::list <int>::iterator *itArr; // MAKE SURE TO FREE THIS AT THE END
    std::list <int> pend;
};

int jacobsthal(int n);
int validateInput(char *input);
int parseInput(char *input);

/*---------List---------*/
int validateInput(char *input);
int parseInput(char *input);
void insert_list(std::list<std::pair<int, int> >& myList, std::list<std::pair<int, int> >::iterator itr);
void recursiveInsertionSort_list(std::list<std::pair<int, int> >& myList, std::list<std::pair<int, int> >::iterator current);
void populateMainAndPend_list(void);
void sortPairs_list();
void mergeInsertSort_list(void);
void populatePair_list();
void displayPairs_list(void);
void insertStranggler_list();

/*---------Vec---------*/
void populatePair_vec(void);
void sortPairs_vec(std::vector< std::pair<int, int> >::iterator it, std::vector< std::pair<int, int> >::iterator end);
void recursiveInsertionSort_vec(std::vector< std::pair<int, int> > &vecArr, unsigned int n);
void insertionSort_vec(std::vector<int> &vecArr);
void displayPairs_vec();
void populateMainAndPend_vec(void);
void mergeinsert(void);
void mergeInsertSortFirstTwoElements_vec();
void mergeInsertSort_vec(void);
void insertStranggler_vec();


#endif