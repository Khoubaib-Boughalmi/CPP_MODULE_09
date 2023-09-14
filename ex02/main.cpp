#include "PmergeMe.hpp"

struct s_struct g_vec_struct;
struct l_struct g_list_struct;


void assembleVectorLogic() {
    std::cout << "Before: ";
    for (size_t i = 0; i < g_vec_struct.initialInputVec.size(); i++)
        std::cout << g_vec_struct.initialInputVec[i] << " ";
    std::cout << std::endl;
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
    std::cout << "After: ";
    for (size_t i = 0; i < g_vec_struct.main.size(); i++)
        std::cout << g_vec_struct.main[i] << " ";
    std::cout << std::endl;
    double elapsedTime = static_cast<double>(end - start) * 1000000.0 / CLOCKS_PER_SEC;
    std::cout << "Time to process a range of " << g_vec_struct.size << " elements with std::vector: " << elapsedTime << " us" <<std::endl;
    std::cout << std::endl;
}

void assembleListLogic() {
    std::cout << "Before: ";
    std::list<int>::iterator lIt;
    for (lIt = g_list_struct.initialInput_list.begin(); lIt != g_list_struct.initialInput_list.end(); ++lIt) {
        std::cout << *lIt << " ";
    }
    std::cout << std::endl;
    clock_t start = clock();
    populatePair_list();
    sortPairs_list();
    recursiveInsertionSort_list(g_list_struct.pair_list, std::prev(g_list_struct.pair_list.end()));
    populateMainAndPend_list();
    mergeInsertSort_list();
    insertStranggler_list();
    clock_t end = clock();
    std::cout << "After: ";
    for (lIt = g_list_struct.main.begin(); lIt != g_list_struct.main.end(); ++lIt) {
        std::cout << *lIt << " ";
    }
    std::cout << std::endl;
    double elapsedTime = static_cast<double>(end - start) * 1000000.0 / CLOCKS_PER_SEC;
    std::cout << "Time to process a range of " << g_vec_struct.size << " elements with std::list: " << elapsedTime << " us" <<std::endl;

}

int main(int argc, char **argv)
{
    std::string input;
    if(argc < 2) {
        std::cout << "Problem with input" << std::endl;
        return (1);
    }
    for (int i = 1; i < argc; i++)
        input = input + argv[i] + " ";  
    if(!validateInput(const_cast<char *>(input.c_str())) || !parseInput(const_cast<char *>(input.c_str()))) {
        std::cout << "Problem with input" << std::endl;
        return (1);
    }
    if(g_vec_struct.initialInputVec.size() < 2)
    {
        std::cout << "Can't sort a single number" << std::endl;
        return (0);
    }
    assembleVectorLogic();
    assembleListLogic();
    return (0);
}