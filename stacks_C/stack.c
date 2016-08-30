/* Stack data structure definition
 * basic usage: gcc -o stk file.c stack.c  -Wall -ansi -pedantic -O2
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"



stack * newStack (int max)
{
	stack *s;	
	s = malloc(sizeof(stack));
	s -> v    = malloc(max*sizeof(pair));
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
	pair * w;
	printf("Reallocation in progress...\n");
	w = malloc(newMax * sizeof(pair));
	for (i = 0; i < s -> max; i++)
		w[i] = s -> v[i];
	free(s -> v);
	s -> v = w;
}

void push (stack *s, pair n)
{
	if (s -> top == s -> max)
		reallocStack(s);
	s -> v[s->top] = n;
	(s -> top)++;
}

pair pop (stack  *s)
{
	/*All checks must be made in the implementation */
	pair n;
	n = s -> v[s -> top - 1];
	(s -> top)--;
	return n;
}


