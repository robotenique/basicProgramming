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
void bThreeSortEven (int **v, int **s, int n);
void bThreeSortOdd (int **v, int **s, int n);
int mod(int a, int b);
void swapPos (int **v, int x, int y);

int main(int argc, char const *argv[]) {
    int n, i;
    int **v;
    /* Leitura */
    scanf("%d",&n);
    v = malloc(2*sizeof(int*));
    if(v == NULL) exit(-1);
    v[0] = malloc(n*sizeof(int));
    v[1] = malloc(n*sizeof(int));
    for (i = 0; i < 2; checkArray(v[i]), i++);
    for (i = 0; i < n; i++) {
        scanf ("%d", &v[0][i]);
        v[1][i] = i;
    }
    /*************************************/
    printf("----Original----\n");
    printArray(v[0],n);
    printArray(v[1],n);
    /*************************************/
    if(n < 3 || !sortArrayCustom (v, n))
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
    for(k = 0; k < n; sortV[0][k] = v[0][k], sortV[1][k] = k, k++);
    for (k = 0; k < 2; checkArray(v[k]), k++);
    heapSort(sortV, n);
    if(!(n % 2)) {
        /* Se o vetor é par, quem estava em posição ímpar só pode ir
         * para posição ímpar se for movendo de 3 em 3, e vice-versa
         * para os pares.
         */
        /*************************************/
        printf("----Calculado----\n");
        printArray(sortV[0],n);
        printArray(sortV[1],n);
        /*************************************/
        for (k = 0; k < n && (sortV[1][k]%2 == v[1][k]%2); k++);
        if (k != n)
            return false;
        bThreeSortEven(v, sortV, n);
    }
    else {
        bThreeSortOdd(v, sortV, n);
    }
    return true;
}

void bThreeSortEven (int **v, int **s, int n) {
    int i, k = 0;
    /* Sorting dos números nas posições pares */
    for (i = n - 2; i >= 0; i -= 2) {
        k = s[1][i];
        while(v[0][i] != s[0][i]) {
            printf("%d\n",k);
            swapPos(v, k, mod(k + 2, n));
            k = mod(k + 2, n);
        }
    }
    printArray(v[0],n);
    /* Sorting dos números nas posições ímpares */
    for (i = n - 1; i >=1; i -= 2) {
        k = s[1][i];
        while (v[0][i] != s[0][i]) {
            printf("%d\n",k);
            swapPos(v, k, mod(k + 2, n));
            k = mod(k + 2, n);
        }
        
    }
    printArray(v[0],n);

}

void bThreeSortOdd (int **v, int **s, int n) {
    exit(-1);
}
/* Implement a ~Pythonic mod operation */
int mod (int a, int b) {
    if(a >= 0)
        return a%b;
    return (b+a)%b;
}

void swapPos (int **v, int x, int y) {
   int aux = v[0][x];
   v[0][x] = v[0][y];
   v[0][y] = aux;
}
/* Create an Array of integers x , x belongs to random numbers :0*/
int* createArray (int n) {
    int i;
    int *v = malloc(n*sizeof(int));
    for (i = 0; i < n; i++)
        v[i] = (int)(rand()%(n*n));
    return v;
}
