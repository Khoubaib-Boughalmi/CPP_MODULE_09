#include <stdio.h>
#include <vector>
#include <stdlib.h>

int *twoWayMergeSort(int *arr1,int *arr2, int size1, int size2) {
    int i = 0;
    int j = 0;
    int k = 0;
    int *mergedArr = (int *)malloc(sizeof(int) * (size2 + size2));

    while (i < size1 && j < size2)
    {
         if(arr1[i] < arr2[j])
            mergedArr[k++] = arr1[i++];
        else
            mergedArr[k++] = arr2[j++];
    }
    for (; i < size1; i++)
        mergedArr[k++] = arr1[i];
    for (; j < size2; j++)
        mergedArr[k++] = arr2[j];
    return mergedArr;
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
         if(leftHandSideArr[i] < rightHandSideArr[j])
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

int main()
{
    std::vector<int> vec;
    int arr[] = {2,8,15,18,5,9,12,17,19,25,30};
    for (size_t i = 0; i < 11; i++)
        vec.push_back(arr[i]);    
    mergeSort(vec, 0, 10);
    int i = 0;
    while (i < 11)
        printf("%d ", vec[i++]);
    return (0);
}