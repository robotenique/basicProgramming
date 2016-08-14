#include <stdio.h> /* printf, scanf, NULL */
#include <stdlib.h> /* malloc, free, rand */


typedef long int intL;
intL *numbersCalc;

int calcCollatz(int n)
{
	int auxN = n;
	int steps = 0;
	while(1)
	{
		if(auxN%2!=0)
		{
			auxN = 3*auxN + 1;
		}
		else
		{
			auxN /= 2;
			if (auxN < n)			
				return steps + numbersCalc[auxN];			
		}
		steps += 1;
	}
}


/* One liner: Check if a number is a power of 2: (n != 0) && ((n & (~n + 1)) == n)*/

int main()
{	
	int begin = 0;
	int end = 0 ;
	int step = 0;
	intL index = 0;
	intL i = 0;	
	intL size;
	
	/* É garantido que:
	    - begin >  0;
	    - end   >= begin;
	    - begin e end são inteiros.
	*/

	/* Versão 1 - Os índices vão de {0,1,2,...,end} endereços */
	scanf("%d %d",&begin,&end);
	size = end * sizeof(numbersCalc[0]);
	printf("%ld\n",size);
	numbersCalc = malloc(size);
	if (numbersCalc == NULL)	
		printf("Alert: Failure in memory allocation, the processing time can increase drastically.\n");	
	numbersCalc[1] = 1;
	for (i = begin; i <= end; i++)
		{
			printf("I = %ld\n",i );
			index ++;
			step = numbersCalc[index] = calcCollatz(i);
			/*printf("%d\n",step );*/
		}	
	printf("%ld\n",sizeof(numbersCalc)/sizeof(numbersCalc[0]));


	/* Main process */
	/* 
	gcc -Wall -Wextra -std=c99 -O4 -o ep1 ep1T.c -Ofast -fwhole-program
	*/


	/*
	for (long long int i = 1; i < 55555555; i++)	
		{
		//printf("i = %llu ,  %llu\n",i,colz(i));
		recColz(i);		
		//colz(i);
		}
	*/
	return 0;
}

/*

long long int colz(long long int n);
long long int recColz(long long int n);

long long int recColz(long long int n)
{	

	if(n==1)
		return 0;
    if(n%2==0)
        return (1+recColz(n/2));
    else
        return (1+recColz(3*n+1));	

}
*/