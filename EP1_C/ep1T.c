#include <stdio.h>

long long int colz(long long int n);
long long int recColz(long long int n);


int cont = 0;
int main()
{	

	/* Main process */
	/*
	gcc -Wall -Wextra -std=c99 -o ep1 ep1T.c -Ofast -fwhole-program

	int val;
	int vezes;
	val = 23;
	*/	
	
	
	for (long long int i = 1; i < 10000000; i++)	
		{
		//printf("i = %llu ,  %llu\n",i,colz(i));
		recColz(i);
		//colz(i);
		}
	printf("%d\n",cont);

	

	return 0;
}

long long int colz(long long int n)
{
	long long int  i = 0;
	while(n!=1)
	{
		while(n%2!=0)
		{
			n = (3*n + 1)/2;
			i+=2;
		}
		while(n%2==0)
		{
			n /= 2;
			i += 1;
		}
		
	}
	return i;	
}
long long int recColz(long long int n)
{	
	if ((n != 0) && ((n & (~n + 1)) == n))
		cont += 1;
	if(n==1)
		return 0;
    if(n%2==0)
        return (1+recColz(n/2));
    else
        return (1+recColz(3*n+1));	

}
