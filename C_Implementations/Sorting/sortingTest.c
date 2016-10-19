#include "sort.h"
#include <stdio.h>
#include <stdlib.h>
float* createArray(int n);

int main(int argc, char const *argv[]) {
    //Initialize an array
    int n = 6;
    float *v =createArray(n);
    /*Sorting Times:
     * int n = 100000, val = 30;
     * Bubble: 37.98s | 2502690779 comps
     * Selection: 15.00s
     * insertion: 9.36s
     * insertion Binary : 6.71s
     * merge: 0.157s
     */
    //bubbleSort(v, n);
    //selectionSort(v, n);
    //insertionSort(v, n);
    //insertionSortLog(v, n);
    heapSort(v, n);
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
