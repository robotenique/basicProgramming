#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

int main(int argc, char const *argv[])
{
	stack * p;
	int i;

	p = newStack(10);
	/* Pushing elements into Stack */
	for (i = 0; i < 10; i ++)	
		push(p,i);
	
	printf("isEmpty? %d\n",isEmpty(*p));

	push(p,123);

	/* Popping elements from stack */
	for (i = 0; i < p -> max; i ++)	
		printf("%d\n",pop(p));

	printf("isEmpty? %d\n",isEmpty(*p));

	
	return 0;
}