#include "PmergeMe.hpp"

std::vector<int> vec;
std::list<int> lst;


void insertionSort(std::vector<int> &arr, int size) {
    int hole;
    int val;
    int i = 1;
    while (i < size)
    {
        val = arr[i];
        hole = i;
        while (hole > 0 && arr[hole - 1] > val)
        {
            arr[hole] = arr[hole - 1];
            hole--;
        }
        arr[hole] = val;
        i++;
    }
}

void merge(std::vector<int> &arr, int left, int middle, int right) {
    int n1 = middle - left + 1;
    int n2 = right - middle;

    std::vector<int> leftHandSideArr(n1);
    std::vector<int> rightHandSideArr(n2);
    for (int i = 0; i < n1; i++)
        leftHandSideArr[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        rightHandSideArr[j] = arr[middle + j + 1];
    
    int i = 0;
    int j = 0;
    int k = left;
    while (i < n1 && j < n2)
    {
         if(leftHandSideArr[i] <= rightHandSideArr[j])
            arr[k++] = leftHandSideArr[i++];
        else
            arr[k++] = rightHandSideArr[j++];
    }
    for (; i < n1; i++)
        arr[k++] = leftHandSideArr[i];
    for (; j < n2; j++)
        arr[k++] = rightHandSideArr[j];
}

void mergeSort(std::vector<int> &arr, int left, int right) {
    int middle;
    if(left < right) {
        middle = left + (right - left) / 2;
        mergeSort(arr, left, middle);
        mergeSort(arr, middle + 1, right);
        merge(arr, left, middle, right);
    } 
}

int validateInput(char *input) {
    size_t i = 0;
    while (input[i] && (input[i] == ' ' || input[i] == '\t' || isdigit(input[i])))
        i++;
    if(input[i])
        return (0);
    return (1);
}


int parseInput(char *input) {
    std::string strVal;
    long val;
    while (*input) {
        while (*input == ' ' || *input == '\t') 
            input++;
        if(*input && isdigit(*input)) {
            strVal = "";
            while (*input && isdigit(*input)) 
            {
                strVal += *input;
                input++;
            }
            val = strtol(strVal.c_str(), NULL, 10);
            if(val > INT_MAX)
                return (0);
            vec.push_back(val);
            lst.push_back(val);
        }
        input++;
    }
    return (1);
}

int main(int argc, char **argv)
{
    if(argc != 2)
    {
        std::cout << "Problem with input" << std::endl;
        return (1);
    }
    if(!validateInput(argv[1]) || !parseInput(argv[1]))
    {
        std::cout << "Problem with input" << std::endl;
        return (1);
    }
   
    // mergeSort(vec, 0, vec.size() - 1);
    insertionSort(vec, 5);
    int i = 0;
    while (i < 5)
        printf("%d ", vec[i++]);
    return (0);
}