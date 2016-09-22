/* Stack data structure definition
 * basic usage: gcc -o stk file.c stack.c  -Wall -ansi -pedantic -O2
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "dataStructs.h"



stack * newStack (int max)
{
    stack *s;
    s = malloc(sizeof(stack));
    s -> v    = malloc(max*sizeof(int));
    s -> top = 0;
    s -> max = max;
    return s;
}

int isEmpty (stack s)
{
    return s.top == 0;
}

void reallocStack(stack *s) {
/*Increase the max in 20% */
    int newMax = s -> max * 1.2;
    int i;
    int * w;
    printf("Reallocation in progress...\n");
    w = malloc(newMax * sizeof(int));
    for (i = 0; i < s -> max; i++)
        w[i] = s -> v[i];
    free(s -> v);
    s -> v = w;
}

void push (stack *s, int n)
{
    if (s -> top == s -> max)
        reallocStack(s);
    s -> v[s->top] = n;
    (s -> top)++;
}

int pop (stack  *s)
{
/*All checks must be made in the implementation */
    int n;
    n = s -> v[s -> top - 1];
    (s -> top)--;
    return n;
}

posArray * criaPosArray (int n) {
    posArray *p_Array;
    p_Array = malloc(sizeof(p_Array));
    if (p_Array == NULL) {
        printf("Erro na alocação de memória, terminando programa...\n");
        exit(-1);
    }
    p_Array->p = malloc(n*sizeof(pos));
    if (p_Array->p == NULL) {
        printf("Erro na alocação de memória, terminando programa...\n");
        exit(-1);
    }
    p_Array->i = 0;
    p_Array->max = n;
    return p_Array;
}

void adicionaPos(posArray *p_Array,pos a) {
    int newMax;
    pos *q;
    int i;
    /* Realoca vetor caso esteja cheio */
    if (p_Array->i == p_Array->max) {
        newMax = p_Array->max * 2;
        q = malloc(newMax * sizeof(pos));
        if (q == NULL) {
            printf("Erro na alocação de memória, terminando programa...\n");
            exit(-1);
        }
        for (i = 0; i < p_Array->max; i++)
            q[i] = p_Array->p[i];
        free(p_Array->p);
        p_Array->p = q;
        p_Array->max = newMax;
    }
    p_Array->p[p_Array->i] = a;
    p_Array->i+=1;
}
