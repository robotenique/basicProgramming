#ifndef _DATA_STRUCTS_H_
#define _DATA_STRUCTS_H_

/* Data structures - Define estuturas de dados usadas no EP.
 * As structs e operações são autoexplicativas.
 */

/* Tipos básicos */
typedef char minINT;
typedef unsigned long int ulint;
typedef enum { false, true } bool;

/* Estruturas */
typedef struct {
       int x;
       int y;
}pos;
typedef struct {
    pos *p;
    unsigned int i;
    unsigned int max;
} posArray;

/* Um movimento é composto da coordenada da peça + número do movimento */
typedef struct {
    unsigned int jCoord;
    minINT mov;
} pMovData;

typedef struct {
    pMovData *p_mov;
    int top;
    int max;
} stack;

/* Operações básicas de pilha */
stack * newStack (int max);
int isEmpty (stack s);
void reallocStack(stack *s);
void push (stack *s, unsigned int jCoord, minINT mov);
pMovData pop (stack  *s);
void destroyStack(stack *s);

/* Operações básicas do posArray */
posArray * newPosArray (int n);
void addPos(posArray *p_Array,pos a);
void destroyPosArray(posArray *p_Array);


#endif
