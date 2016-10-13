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
bool isPossible(int v[], int n);

int main(int argc, char const *argv[]) {
    int n, k;
    int *v;
    /* Leitura */
    scanf("%d",&n);
    v = malloc(sizeof(int));
    checkArray(v);
    for (k = 0; k < n; k++)
        scanf ("%d", &v[k]);

     /* Verificar se é possível*/
     if(!isPossible(v, n)) {
         printf("Nao e possivel\n");
         exit(0);
     }


    return 0;
}

bool isPossible(int v[], int n) {
    int i;
    int *pVector;
    if (!(n % 2))
        return true;
    pVector = malloc(n * sizeof(int));
    printArray(v, n);
    checkArray(pVector);
    for (i = 0; i < n; pVector[i] = v[i] % 2, i++);
    printArray(pVector, n);
    return true;

}


/* Testing functions */
int* createArray (int n) {
    int i;
    int *v = malloc(n*sizeof(int));
    for (i = 0; i < n; i++)
        v[i] = (int)(rand()%(n*n));
    return v;
}
