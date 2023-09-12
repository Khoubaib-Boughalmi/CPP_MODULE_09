#include "PmergeMe.hpp"
struct v_struct g_vec_struct;
struct l_struct g_list_struct;

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
    if(g_vec_struct.initialInputVec.size() < 2)
        return (0);
    populatePairVec();
    populatePair_list();
    displayPairs_list();
    std::cout << std::endl; 
    std::vector< std::pair<int, int> >::iterator pairVecIterator;
    std::vector< std::pair<int, int> >::iterator pairVecEndIterator;
    pairVecIterator = g_vec_struct.pairVec.begin();
    pairVecEndIterator = g_vec_struct.pairVec.end();
    sortVecPairs(pairVecIterator, pairVecEndIterator);
    sortPairs_list();
    displayPairs_list();
    populatePair_list();
    recursiveInsertionSortVec(g_vec_struct.pairVec, g_vec_struct.pairVec.size());
    recursiveInsertionSort_list(g_list_struct.pairList, g_list_struct.pairList.end()--);
    populateMainAndPendVec();
    populateMainAndPend_list();
    std::cout << "\n--------------------\n";
    mergeInsertSortVec();
    mergeInsertSort_list();
    std::cout << "Vectors: ";
    for (size_t i = 0; i < g_vec_struct.main.size(); i++)
        std::cout << g_vec_struct.main[i] << " ";

    std::cout << "\nList:    "; 
    std::list<int>::iterator lIt = g_list_struct.main.begin();
    for (; lIt != g_list_struct.main.end(); lIt++)
    {
        std::cout << *lIt << " ";
    }
    std::cout << std::endl; 

    return (0);
}