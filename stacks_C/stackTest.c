#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

int main(int argc, char const *argv[])
{
	stack * p;
	int i;

	p = newStack(10);
	for (i = 10; i > 0; i --)	
		push(p,i);
	for (i = 0; i < p -> top; i ++)
		printf("%d\n",pop(p));
	
	return 0;
}