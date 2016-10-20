#include "sort.h"
#include <stdio.h>
#include <stdlib.h>
float* createArray(int n);

int main(int argc, char const *argv[]) {
    //Initialize an array
    int n = 100;
    float *v =createArray(n);

    /*Sorting Times:
     * int n = 100000, val = 30;
     * Bubble: 37.98s | 2502690779 comps
     * Selection: 15.00s
     * insertion: 9.36s
     * insertion Binary : 6.71s
     * merge: 0.031s | 26.553s p/ 100mi
     * heap: 0.030s
     *
     */
    //bubbleSort(v, n);
    //selectionSort(v, n);
    //insertionSort(v, n);
    //insertionSortLog(v, n);
    //float *c = malloc(sizeof(float)*n); mergeSort(v,c,0,n-1,0);
    //heapSort(v, n);
    quickSort(v,0,n-1);
    printArray(v,n);
    //printf("comparações (heapSort) = %llu\n",x);
    return 0;
}

float* createArray(int n) {
    float *v = malloc(n*sizeof(float));
    for (int i = 0; i < n; i++)
        v[i] = (float)(rand()%n);
    return v;
}
