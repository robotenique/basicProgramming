#include <stdio.h> /* printf, scanf, NULL */
#include <stdlib.h> /* malloc, free, rand */

/* Mudar nome das variaveis 2147483647 1000000 */

typedef unsigned long int uLint;
typedef unsigned short int uSint;
typedef unsigned int uInt;
static unsigned short int *numbersCalc;

uSint calcCollatz(uInt n)
{
	uLint auxN = n;
	uSint steps = 1;
	
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
	uInt begin = 0;
	uInt end = 0 ;
	uInt i = 0;	
	
	/* É garantido que:
	    - begin >  0;
	    - end   >= begin;
	    - begin e end são inteiros.
	*/

	/* Versão 1 - Os índices vão de {0,1,2,...,end} endereços */
	scanf("%u %u",&begin,&end);
	numbersCalc = malloc(end * sizeof(numbersCalc[0]));	
	if (numbersCalc == NULL) {
		printf("Alert: Failure in memory allocation, the processing time can increase drastically.\n");	
		return 1;
	}
	numbersCalc[1] = 0;	
	if (begin==1)
	{
		printf("0\n");
		begin ++;
	}
	for (i = begin; i <= end; i++){		
		numbersCalc[i] = calcCollatz(i);		
		if (i==2147483647)
		{
			printf("PRINTANDO %hu\n",numbersCalc[i] );
		}
		/*if (i>=begin)
			printf("colz(%u) = %hu\n", i,numbersCalc[i] );
		*/
	}
	free(numbersCalc);
	

	return 0;
}

