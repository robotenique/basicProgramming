#ifndef _stack_h
#define _stack_h

typedef struct 
{
	/*Int type stack */
	char *v;
	int top;
	int max;
} stack;

stack * newStack (int max);
int isEmpty (stack s);
void reallocStack(stack *s);
void push (stack *s, char n);
char pop (stack  *s);

#endif