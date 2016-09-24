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
    s -> p_mov = malloc(max*sizeof(pMovData));
    s -> top = 0;
    s -> max = max;
    return s;
}

int isEmpty (stack s)
{
    return s.top == 0;
}

void reallocStack(stack *s)
{
/*Doubles the maximum of elements in the stack */
    int newMax = s -> max * 2;
    int i;
    pMovData * w;
    w = malloc(newMax * sizeof(pMovData));
    for (i = 0; i < s -> max; i++)
        w[i] = s -> p_mov[i];
    free(s -> p_mov);
    s -> p_mov = w;
    s -> max = newMax;
}

void push (stack *s, unsigned int jCoord, minINT mov)
{
    pMovData x;
    x.jCoord = jCoord;
    x.mov = mov;
    if (s -> top == s -> max)
        reallocStack(s);
    s -> p_mov[s->top] = x;
    (s -> top)++;
}

pMovData pop (stack  *s)
{
/*All checks must be made in the implementation */
    pMovData x;
    x = s -> p_mov[s -> top - 1];
    (s -> top)--;
    return x;
}

posArray * criaPosArray (int n) {
    posArray *p_Array;
    p_Array = malloc(sizeof(p_Array));
    if (p_Array == NULL)
        exit(-1);
    p_Array->p = malloc(n*sizeof(pos));
    if (p_Array->p == NULL)
        exit(-1);
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
        if (q == NULL)
            exit(-1);

        for (i = 0; i < p_Array->max; i++)
            q[i] = p_Array->p[i];
        free(p_Array->p);
        p_Array->p = q;
        p_Array->max = newMax;
    }
    p_Array->p[p_Array->i] = a;
    p_Array->i+=1;
}
