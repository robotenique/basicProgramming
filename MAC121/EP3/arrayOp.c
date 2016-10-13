#include "arrayOp.h"
#include <stdio.h>
void swap (int v[], int x, int y);
void toDown (int v[], int n, int i);
void heapify (int v[], int n);

void toDown (int v[], int n, int i) {
    int x = v[i];
    int parent = i;
    int son = 2*i+1;
    while (son < n) {
        if (son + 1 < n && v[son + 1] > v[son])
            son = son + 1;
        if (x > v[son])
            break;
        v[parent] = v[son];
        parent = son;
        son = 2*son + 1;
    }
    v[parent] = x;
}

void heapify (int v[], int n) {
    int i;
    for (i = (n-2)/2; i >=0;toDown(v, n, i), i--);
}


void heapSort (int v[], int n) {
    int i;
    heapify(v, n);
    for (i = n-1; i > 0; i--){
        swap(v, 0, i);
        toDown(v, i, 0);
    }
}

void swap (int v[], int x, int y) {
    int aux = v[x];
    v[x] = v[y];
    v[y] = aux;
}

void printArray (int v[], int n) {
    int k = 0;
    printf("[%2d,",v[k]);
    for (k = 1; k < n - 1; printf(" %2d,",v[k]), ++k);
    printf(" %2d]",v[k]);
    printf("\n");
}
