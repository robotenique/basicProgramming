#ifndef _SORT_H_
#define  _SORT_H_

typedef unsigned long long ull;
//Search
int linearSearch(float v[], int n, float x);
int binarySearch (float v[], int n, float x);
int binarySearchRec (float v[], int b, int e , float x);

//Sorting
ull bubbleSort(float v[], int n);
ull insertionSort(float v[], int n);
ull insertionSortLog(float v[], int n);
ull selectionSort(float v[], int n);
ull quickSort(float v[], int n);
ull heapSort(float v[], int n);
ull mergeSort(float v[], float aux[], int ini, int end, ull cmp);


//Auxiliar
void printArray (float *array, int n);
#endif
