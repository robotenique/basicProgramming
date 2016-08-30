/*
 * Ex1 Stack List
 * Reverse the letters of a string, keeping the Word original order
 * ---->TYPE TO CHANGE =  char
 */

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
 void sepWord (char *s, int n);

 int main(int argc, char const *argv[])
 {
 	char *s;
 	int n;
 	printf("Length: "); 
 	scanf("%d ",&n); 	
 	s = malloc(n * sizeof(char)); 	
 	fgets(s,n+1,stdin); 	
 	printf("\nString ='%s'\n",s );
 	sepWord(s,n);

 	return 0;
 }

 void imprimeTest (char *s, int i, int j) {
 	stack *p;
 	int qt = j - i;
 	p = newStack(j - i); 	
 	for (i = i; i < j; i++)
 		push(p,s[i]);
 	
 	for (i = 0; i < qt; i++) 	
 		printf("%c",pop(p));
 		
 	
 	printf(" ");
 	
 }

 void sepWord (char *s, int n) { 
 	int i,j,ok;
 	i = 0;
 	ok = 0;
 	while(!ok) {
 		for (j = i; s[j]!=' ' && s[j]!='\0' && s[j]!='\n'; j++);
 		imprimeTest(s,i,j); 		
 		if (j >= n)
 			ok = 1;
 		else
 			i = j + 1;
 	}
 	
 	/*invertWord(s,i,j);*/

 	


 }

 