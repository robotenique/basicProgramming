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
bool sortArrayCustom (int **v, int n);

int main(int argc, char const *argv[]) {
    int n, k;
    int **v;
    /* Leitura */
    scanf("%d",&n);
    v = malloc(2*sizeof(int*));
    if(v == NULL) exit(-1);
    v[0] = malloc(n*sizeof(int));
    v[1] = malloc(n*sizeof(int));
    for (k = 0; k < 2; checkArray(v[k]), k++);
    for (k = 0; k < n; k++) {
        scanf ("%d", &v[0][k]);
        v[1][k] = k%2;
    }
    printf("----Original----\n");
    printArray(v[0],n);
    printArray(v[1],n);
    if(!sortArrayCustom (v, n))
        printf("Nao e possivel\n");



    return 0;
}

bool sortArrayCustom (int **v, int n) {
    int k;
    /* Cópia do vetor original */
    int **sortV = malloc(2*sizeof(int*));
    sortV[0] = malloc(n*sizeof(int));
    sortV[1] = malloc(n*sizeof(int));
    if(sortV == NULL) exit(-1);
    for(k = 0; k < n; sortV[0][k] = v[0][k], sortV[1][k] = k % 2, k++);
    for (k = 0; k < 2; checkArray(v[k]), k++);
    heapSort(sortV, n);
    if(!(n % 2)) {
        /* Se o vetor é par, quem estava em posição ímpar só pode ir
         * para posição ímpar se for movendo de 3 em 3, e vice-versa
         * para os pares.
         */
        printf("----Calculado----\n");
        printArray(sortV[0],n);
        printArray(sortV[1],n);
        for (k = 0; k < n && (sortV[1][k] == v[1][k]); k++);
        if (k != n)
            return false;

    }
    return true;
}


/* Create an Array of integers x , x belongs to []*/
int* createArray (int n) {
    int i;
    int *v = malloc(n*sizeof(int));
    for (i = 0; i < n; i++)
        v[i] = (int)(rand()%(n*n));
    return v;
}
