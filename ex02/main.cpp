#include "PmergeMe.hpp"

struct s_struct g_vec_struct;
struct l_struct g_list_struct;


void assembleVectorLogic() {
    clock_t start = clock();
    populatePair_vec();
    std::vector< std::pair<int, int> >::iterator pairVecIterator;
    std::vector< std::pair<int, int> >::iterator pairVecEndIterator;
    pairVecIterator = g_vec_struct.pairVec.begin();
    pairVecEndIterator = g_vec_struct.pairVec.end();
    sortPairs_vec(pairVecIterator, pairVecEndIterator);
    recursiveInsertionSort_vec(g_vec_struct.pairVec, g_vec_struct.pairVec.size());
    populateMainAndPend_vec();
    mergeInsertSort_vec();
    insertStranggler_vec();
    clock_t end = clock();
    double elapsedTime = static_cast<double>(end - start) * 1000000.0 / CLOCKS_PER_SEC;
    std::cout << "Time to process a range of " << g_vec_struct.size << " elements with std::vector: " << elapsedTime << " us" <<std::endl;
    // for (size_t i = 0; i < g_vec_struct.main.size(); i++)
    //     std::cout << g_vec_struct.main[i] << " ";
    std::cout << std::endl;
}

void assembleListLogic() {
    clock_t start = clock();
    populatePair_list();
    sortPairs_list();
    recursiveInsertionSort_list(g_list_struct.pair_list, std::prev(g_list_struct.pair_list.end()));
    populateMainAndPend_list();
    mergeInsertSort_list();
    insertStranggler_list();
    // std::list<int>::iterator lIt;
    // for (lIt = g_list_struct.main.begin(); lIt != g_list_struct.main.end(); ++lIt) {
    //     std::cout << *lIt << " ";
    // }
    clock_t end = clock();
    double elapsedTime = static_cast<double>(end - start) * 1000000.0 / CLOCKS_PER_SEC;
    std::cout << "Time to process a range of " << g_vec_struct.size << " elements with std::list: " << elapsedTime << " us" <<std::endl;

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
    if(g_vec_struct.initialInputVec.size() < 2)
        return (0);
    assembleVectorLogic();
    assembleListLogic();
    return (0);
}