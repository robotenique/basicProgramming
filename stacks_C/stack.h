#ifndef _stack_h
#define _stack_h

typedef struct 
{
	int r,c;	
} pair;


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

#endif