#ifndef _DATA_STRUCTS_H_
#define _DATA_STRUCTS_H_
typedef char minINT;
typedef unsigned long int ulint;
typedef enum { false, true } bool;
typedef struct {
       int x;
       int y;
}pos;
typedef struct {
    pos *p;
    unsigned int i;
    unsigned int max;
} posArray;

typedef struct {
    unsigned int jCoord;
    minINT mov;
} pMovData;

typedef struct {
    /*pMovDt type stack */
    pMovData *p_mov;
    int top;
    int max;
} stack;

stack * newStack (int max);
int isEmpty (stack s);
void reallocStack(stack *s);
void push (stack *s, unsigned int jCoord, minINT mov);
pMovData pop (stack  *s);
posArray * newPosArray (int n);
void addPos(posArray *p_Array,pos a);
void destroyPosArray(posArray *p_Array);
void destroyStack(stack *s);


#endif
