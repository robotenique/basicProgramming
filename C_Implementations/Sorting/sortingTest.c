#include "sort.h"
#include <stdio.h>
#include <stdlib.h>
float* createArray(int n);

int main(int argc, char const *argv[]) {
    //Initialize an array
    int n = 100000, val = 30, x;
    float *v =createArray(n);
    //for (int k = 0; k < n; printf("%.2f |",v[k]), k++);
    //x = linearSearch(v,n,val);
    //printf("Linear Search (%d) = %d\n",val,x);

    /*Sorting Times:
     * Bubble: 48.01s
     * Selection: 15.00s
     * insertion: 9.36s
     * insertion Binary : 6.71s
     */
    bubbleSort(v,n);
    //selectionSort(v,n);
    //insertionSort(v,n);
    //insertionSortLog(v,n);
    for (int k = 0; k < n; printf("%.2f |",v[k]), k++);

    return 0;
}

float* createArray(int n) {
    float *v = malloc(n*sizeof(float));
    for (int i = 0; i < n; i++)
        v[i] = (float)(rand()%n);
    return v;
}
