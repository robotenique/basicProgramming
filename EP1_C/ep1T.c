#include <stdio.h> /* printf, scanf, NULL */
#include <stdlib.h> /* malloc, free, rand */

/* Mudar nome das variaveis 2147483647 1000000 

*/

typedef unsigned long int uLint;
typedef unsigned short int uSint;
typedef unsigned int uInt;
static unsigned short int *numbersCalc;

uSint calcCollatz(uInt n)
{
	/* uLint auxN = n; */
	uLint auxN = n;
	uSint steps = 1;
	
	
	while(1)
	{	
		
		if(auxN%2!=0)
		{
			auxN = (3*auxN + 1)/2;
			steps += 2;
		}
		else
		{
			auxN >>= 1;
			if (auxN < n){						
				return steps + numbersCalc[auxN];
			}
			steps += 1;			
		}
		
	
	}
}



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

	scanf("%u %u",&begin,&end);
	numbersCalc = calloc(end,sizeof(numbersCalc[0]));	
	if (numbersCalc == NULL) {
		printf("Erro na alocação de memória, verifique a entrada novamente!\n");	
		return 1;
	}
	numbersCalc[1] = 1;	
	if (begin==1)
	{
		printf("0\n");
		begin ++;
	}
	for (i = 2; i <=end; i++){
		numbersCalc[i] = calcCollatz(i);
		if(i>=begin)
			printf("colz(%u) = %hu\n", i,(numbersCalc[i]-1) );
	}
	

	 /* No need to free() as the program is terminated at this point */
	
	

	return 0;
}

