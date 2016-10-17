/*
 * @author: Juliano Garcia de Oliveira
 * nº usp = 9277086
 * MAC0121
 * 17/10/2016
 * header file para operações de função
 */
#ifndef _ARRAYOP_H_
#define _ARRAYOP_H_

/* Definição de tipos */
typedef enum { false, true } bool;
typedef char minINT;

void heapSort (int **v, int n);
void checkArray(int *v);
bool isEqual(int *a, int *b, int n);
bool isSorted(int *v, int n);

#endif
