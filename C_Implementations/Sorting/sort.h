#ifndef _SORT_H_
#define  _SORT_H_

//Search
int linearSearch(float v[], int n, float x);
int binarySearch (int *array, int n, int x);
int binarySearchRec (int *array, int b, int e , int x);
//Sorting
int bubbleSort();
int insertionSort();
int selectionSort();
int mergeSort();
int quickSort();
int heapSort();

#endif
