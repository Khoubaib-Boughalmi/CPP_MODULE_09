#include <stdio.h>
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

int main()
{
    int arr1[] = {2,8,15,18};
    int arr2[] = {5,9,12,17,19,25,30};
    int *mergedArr;
    mergedArr = twoWayMergeSort(arr1, arr2, 4, 7);
    int i = 0;
    while (i < 10)
        printf("%d ", mergedArr[i++]);
    return (0);
}