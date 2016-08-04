#include <stdio.h>
#include <math.h> 

long long int colz(long long int n);
long long int recColz(long long int n);
int calcLog2(long long int v);

/* One liner: Check if a number is a power of 2: (n != 0) && ((n & (~n + 1)) == n)*/

int main()
{	

	/* Main process */
	/* 
	gcc -Wall -Wextra -std=c99 -O4 -o ep1 ep1T.c -Ofast -fwhole-program


	int val;
	int vezes;
	val = 23;

	TESTE x = 55555555 iterações:
	 --> COM LOG (LinuxLow): 
	 	1m6.878s
	 	1m0.982s
	 --> SEM LOG (LinuxLow):
		0m39.800s





	*/	
	
	



	for (long long int i = 1; i < 55555555; i++)	
		{
		//printf("i = %llu ,  %llu\n",i,colz(i));
		recColz(i);		
		//colz(i);
		}

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
		return (int)log2(n);
		
	if(n==1)
		return 0;
    if(n%2==0)
        return (1+recColz(n/2));
    else
        return (1+recColz(3*n+1));	

}


int calcLog2(long long int v)
{
static const long long int b[] = {0xAAAAAAAA, 0xCCCCCCCC, 0xF0F0F0F0, 
                                 0xFF00FF00, 0xFFFF0000};
register long long int r = (v & b[0]) != 0;
for (int i = 4; i > 0; i--) // unroll for speed...
{
  r |= ((v & b[i]) != 0) << i;
}
return r;
}
