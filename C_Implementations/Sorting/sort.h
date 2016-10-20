#ifndef _SORT_H_
#define  _SORT_H_

typedef unsigned long long ull;
//Search
int linearSearch(float v[], int n, float x);
int binarySearch (float v[], int n, float x);
int binarySearchRec (float v[], int b, int e , float x);

//Sorting
void bubbleSort(float v[], int n);
void insertionSort(float v[], int n);
void insertionSortLog(float v[], int n);
void selectionSort(float v[], int n);
void quickSort(float v[], int ini, int fim);
void heapSort(float v[], int n);
ull mergeSort(float v[], float aux[], int ini, int end, ull cmp);


//Auxiliar
void printArray (float v[], int n);
void swap(float v[], int a, int b);

#endif
