#ifndef _DATA_STRUCTS_H_
#define _DATA_STRUCTS_H_
typedef char minINT;
typedef enum { false, true } bool;
typedef struct {
      unsigned int x;
     unsigned  int y;
}pos;
typedef struct {
    pos *p;
    unsigned int i;
    unsigned int max;
} posArray;
typedef struct
{
    /*Int type stack */
    int *v;
    int top;
    int max;
} stack;

stack * newStack (int max);
int isEmpty (stack s);
void reallocStack(stack *s);
void push (stack *s, int n);
int pop (stack  *s);
posArray * criaPosArray (int n);
void * adicionaPos(posArray *p_Array,pos a);


#endif
