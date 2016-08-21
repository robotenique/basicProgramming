/* Stack data structure definition */

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"



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

void reallocStack(stack *s)
{
	/*Increase the max in 20% */
	int newMax = s -> max * 1.2;
	int i;
	int * w;

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


