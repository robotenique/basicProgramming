/*
 * @author: Juliano Garcia de Oliveira
 * nº usp = 9277086
 * MAC0121
 * 17/10/2016
 */
#include <stdlib.h>
#include <stdio.h>
#include "arrayOp.h"

int* createArray(int n);

int main(int argc, char const *argv[]) {
    int *v = createArray(90);
    printArray(v,90);
    heapSort(v, 90);
    printArray(v,90);



    return 0;
}


/* Testing functions */
int* createArray (int n) {
    int i;
    int *v = malloc(n*sizeof(int));
    for (i = 0; i < n; i++)
        v[i] = (int)(rand()%(n*n));
    return v;
}
