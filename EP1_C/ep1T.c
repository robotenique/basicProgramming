#include <stdio.h> /* printf, scanf, NULL */
#include <stdlib.h> /* malloc, free, rand */

/* Mudar nome das variaveis */
typedef long int intL;
static unsigned short int *numbersCalc;

unsigned short int calcCollatz(int n)
{
	unsigned int auxN = n;
	unsigned short int steps = 1;
	while(1)
	{
		if(auxN%2!=0)
		{
			auxN = 3*auxN + 1;
		}
		else
		{
			auxN = auxN >> 1;
			if (auxN < n)			
				return steps + numbersCalc[auxN];			
		}
		steps += 1;
	}
}


/* One liner: Check if a number is a power of 2: (n != 0) && ((n & (~n + 1)) == n)*/

int main()
{	
	unsigned int begin = 0;
	unsigned int end = 0 ;
	unsigned int i = 0;	
	
	/* É garantido que:
	    - begin >  0;
	    - end   >= begin;
	    - begin e end são inteiros.
	*/

	/* Versão 1 - Os índices vão de {0,1,2,...,end} endereços */
	scanf("%u %u",&begin,&end);
	numbersCalc = malloc(end * sizeof(numbersCalc[0]));	
	if (numbersCalc == NULL)	
		printf("Alert: Failure in memory allocation, the processing time can increase drastically.\n");	
	numbersCalc[1] = 1;
	for (i = 2; i <= end; i++){		
		numbersCalc[i] = calcCollatz(i);		
		if (i>=begin)
			printf("colz(%u) = %hu\n", i,numbersCalc[i]-1 );
	}

	return 0;
}

