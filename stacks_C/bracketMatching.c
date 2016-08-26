/*
 * Bracket Matching using Stacks.
 * Good bracket sequences: {([]((({()()}{()})){}))} , {()()[(){}(({{}}))]}
 * Bad bracket sequences:  [(]) , ([{{{(})}}}]) , {(({[{()}]}))}]
 * IMPORTANT: THE STACK FILE NEED TO BE CHANGED TO THE APPRIATE TYPE.
 * ---->TYPE TO CHANGE =  char
 */

#include <stdio.h>
#include "stack.h"


int isMatched(char s[]);
int match (char c, char s);

int main(int argc, char const *argv[])
{
	char s[100];
	scanf("%s",s);
	printf("Bracket phrase = %s\n",s );
	printf("isMatched = %d\n",isMatched(s));
	return 0;
}


int isMatched (char s[])
{
	/* Receives a string with the sequence and returns 1 if the matching is correct
	 * returns 0 if it's not
	 */

	 stack *p;
	 int i, ok;
	 char c;
	 
	 ok = 1;
	 p = newStack(100);
	 for (i = 0; s[i]!='\0' && ok;i++) {	 	
	 	if (s[i] == '(' || s[i] == '[' || s[i] == '{')
	 		push(p,s[i]);	 	
	 	else {
	 		/*We suppose is something closing */
	 		if (isEmpty(*p)){
	 			ok = 0;	 			
	 		}
	 		else {
	 			c = pop(p);
	 			if (!match(c,s[i]))
	 				ok = 0;
	 		}
	 	}	 		
	 }
 if (!isEmpty(*p))
 	ok = 0;	 
 return ok;
 }
	 


int match (char c, char s) {
	
	if (s == ')' && c == '(')
		return 1;
	if (s == ']' && c == '[')
		return 1;
	if (s == '}' && c == '{')
		return 1;
	return 0;
}