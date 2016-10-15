/*
 * @author: Juliano Garcia de Oliveira
 * nº usp = 9277086
 * MAC0121
 * 17/10/2016
 */
#include <stdlib.h>
#include <stdio.h>
#include "arrayOp.h"

/* TODO: Consertar loop infinito p/ pares
 *       Consertar calculo p/ ímpares
 *       Teste de mesa com ímpares (??)
 */
int* createArray(int n);
bool sortArrayCustom (int **v, int n);
void bThreeSortOdd (int **v, int **s, int n);
int mod(int a, int b);
void swapPos (int **v, int x, int y);
void swapPosAndIndex (int **v, int **s, int x, int y);
void bubble3(int *array, int n, int ini);

int main(int argc, char const *argv[]) {
    int n, i;
    int **v;
    /* Leitura */
    scanf("%d",&n);
    v = malloc(3*sizeof(int*));
    if(v == NULL) exit(-1);
    v[0] = malloc(n*sizeof(int));
    v[1] = malloc(n*sizeof(int));
    for (i = 0; i < 2; checkArray(v[i]), i++);
    for (i = 0; i < n; i++) {
        scanf ("%d", &v[0][i]);
        v[1][i] = i;
    }
    /*************************************/
    /*printf("*************************************\n");

    printf("----Original----\n");
    printf("V[0] = ");
    printArray(v[0],n);
    printf("V[1] = ");
    printArray(v[1],n);
    */
    /*************************************/
    if(n < 3 || !sortArrayCustom (v, n))
        printf("Nao e possivel\n");
    printArray(v[0],n);
    return 0;
}

void bubble3(int *v, int n, int ini) {
    int i, j, temp;
    for(i = ini; i < n; i++) {
      bool flag = false;
       for(j = 0; j < n - i - 1; j++) {
          if(v[j] > v[mod(j+2,n)]) {
            flag = true;
             temp = v[mod(j+2,n)];
             v[mod(j+2,n)] = v[j];
             v[j] = temp;
             printf("%d\n",j);
          }
       }
      if(!flag){
         return;
      }
   }
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
    printf("HEAPFYED\n");
    /*************************************/
    printf("----Calculado----\n");
    printf("s[0] = ");
    printArray(sortV[0],n);
    printf("s[1] = ");
    printArray(sortV[1],n);
    printf("*************************************\n");
    /*************************************/
    if(!(n % 2)) {
        /* Se o vetor é par (i.e. n%2 = 0), quem estava em posição ímpar só
         * pode ir para posição ímpar pulando de 3 em 3, e vice-versa  para
         * os pares.
         */
        for (k = 0; k < n && (sortV[1][k]%2 == v[1][k]%2); k++);
        if (k != n)
            return false;
        bubble3(v[0],n,0);
        bubble3(v[0],n,1);
    }
    else {
        /* Se o vetor tem tamanho ímpar, qualquer elemento pode acessar
         * qualquer posição do vetor pulando de 3 em 3, logo é possível
         * ordernar o vetor (Todo elemento pode ir para a posição correta)!
         */
        /* V[1] agora possui os indíces onde cada número deve ficar após
         * a ordenação do vetor.
         */
        for(k = 0; k < n; v[1][sortV[1][k]] = k, k++);
        bThreeSortOdd(v, sortV, n);
    }
    return true;
}

void bThreeSortOdd (int **v, int **s, int n) {
    int total = n, i, pos, aux1, aux2;
    bool flag;
    /* Primeira posição a ser preenchida */
    i = mod(n - 2 , n);
    while(total > 1) {
    /* Posição do elemento que deve ir para i */
        pos = s[1][i];
        flag = false;
        while (v[0][i] != s[0][i]) {
            flag = true;
            swapPosAndIndex(v, s, pos, mod(pos + 2, n));
            printf("%d\n", pos);
            pos = mod(pos + 2, n);
        }
        /* Trocando as posições dos índices (corrige erros se o número já
         *  está na posição correta desde o início!).
         */
         if(flag) {
            aux1 = s[1][i];
            aux2 = v[1][i];
            s[1][i] = i;
            s[1][aux2] = aux1;
             v[1][i] = i;         
            v[1][aux1] = aux2;
         }
        i = mod(i - 2, n);
        total--;
    }
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

void swapPosAndIndex (int **v, int **s, int x, int y) {
    int aux1 = v[1][x], aux2 = s[1][v[1][x]];
    swapPos(v,x,y);
    s[1][v[1][x]] = s[1][v[1][y]];
    s[1][v[1][y]] = aux2;
    v[1][x] = v[1][y];
    v[1][y] = aux1;
}

/* Create an Array of integers x , x belongs to random numbers :0*/
int* createArray (int n) {
    int i;
    int *v = malloc(n*sizeof(int));
    for (i = 0; i < n; i++)
        v[i] = (int)(rand()%(n*n));
    return v;
}
