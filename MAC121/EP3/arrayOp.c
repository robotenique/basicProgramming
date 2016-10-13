#include "arrayOp.h"
#include <stdio.h>
#include <stdlib.h>
void swap (int **v, int x, int y);
void toDown (int**v, int n, int i);
void heapify (int **v, int n);

void toDown (int **v, int n, int i) {
    int x = v[0][i];
    int p = v[1][i];
    int parent = i;
    int son = 2*i+1;
    while (son < n) {
        if (son + 1 < n && v[0][son + 1] > v[0][son])
            son = son + 1;
        if (x > v[0][son])
            break;
        v[0][parent] = v[0][son];
        v[1][parent] = v[1][son];
        parent = son;
        son = 2*son + 1;
    }
    v[0][parent] = x;
    v[1][parent] = p;

}

void heapify (int **v, int n) {
    int i;
    for (i = (n-2)/2; i >=0;toDown(v, n, i), i--);
}


void heapSort (int **v, int n) {
    int i;
    heapify(v, n);
    for (i = n-1; i > 0; i--){
        swap(v, 0, i);
        toDown(v, i, 0);
    }
}

void swap (int **v, int x, int y) {
    int aux = v[0][x];
    int aux2 = v[1][x];
    v[0][x] = v[0][y];
    v[1][x] = v[1][y];
    v[0][y] = aux;
    v[1][y] = aux2;
}

void checkArray (int v[]) {
    if(v == NULL) {
        printf("ERRO FATAL NA ALOCAÇÃO DE MEMÓRIA! Saindo do programa...\n");
        exit(-1);
    }
}

void printArray (int v[], int n) {
    int k = 0;
    printf("[%2d,",v[k]);
    for (k = 1; k < n - 1; printf(" %2d,",v[k]), ++k);
    printf(" %2d]",v[k]);
    printf("\n");
}
