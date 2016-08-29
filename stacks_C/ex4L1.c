/*
 * Ex1 Stack List
 * Verify if a sequence has symmetry around the 'c' letter
 * ---->TYPE TO CHANGE =  char
 */

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

 int isSymmetric (char *s);
 int main(int argc, char const *argv[])
 {
 	char *s;
 	int ok,n;
 	printf("Length: ");
 	scanf("%d",&n);
 	s = malloc(n * sizeof(char));
 	printf("String: ");
 	scanf("%s",s);
 	ok = isSymmetric(s);
 	printf("HAS SYMMETRY? %d \n",ok);
 	return 0;
 }

 int isSymmetric (char *s)
 {
 	int i,j,k,ok;
 	stack *wList;
 	
 	i = 0;
 	ok= 0;
 	while (s[i]!='c')
 		i++; 	
 	j = i;
 	i += 1;
 	while (s[i]!='\0')		
 		i++; 
 	if (j != i-1-j) { 		
 		return NULL;
 	}
 	i = 0;
 	wList = newStack(j);
 	while (s[i]!='c') {
 		push(wList,s[i]);
 		i++;
 	}
 	for (i = i + 1; s[i]!='\0' && ok == 0; i++) { 		
 		if (pop(wList) != s[i])
 			ok = 1;

 	}

 	return !ok;
 }