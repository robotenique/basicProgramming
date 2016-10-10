#ifndef _SORT_H_
#define  _SORT_H_

//Search
int linearSearch(float v[], int n, float x);
int binarySearch (float v[], int n, float x);
int binarySearchRec (float v[], int b, int e , float x);
//Sorting
void bubbleSort(float v[], int n);
void insertionSort(float v[], int n);
void insertionSortLog(float v[], int n);
void selectionSort(float v[], int n);
void mergeSort(float v[], int n);
void quickSort(float v[], int n);
void heapSort(float v[], int n);

#endif
