/*
 * Ex9 Stack List
 * Backtrack in chess board
 * ---->TYPE TO CHANGE =  pair
 */

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
 int ** criaMatriz(int m, int n);
 int bishopChess (int n, int k);


 int main(int argc, char const *argv[])
 {
    int n;
    int **m;
    printf("Input the n: ");
    scanf("%d",&n);    
    /*bishopChess(int n);*/
    m = criaMatriz(n,n);
    printf("%d\n",m[0][0] );
    return 0;
 }

 int ** criaMatriz(int m, int n) { 
    int **A;
    int i;
    A = calloc(m , sizeof(int *));
    for (i = 0; i < m; i++)       
        A[i] = calloc(n , sizeof(int));
    
    return A;
 }

int bishopChess (int n, int k) { 
    int **board;    
    stack *mem;


    mem   = newStack(n*n);
    board = criaMatriz(n,n);
    if (k > n) return 0;


}

 