/*
 * Knight's Tour Puzzle :  Backtrack 
 * IMPORTANT: THE STACK FILE NEED TO BE CHANGED TO THE APPROPRIATE TYPE.
 * ---->TYPE TO CHANGE =  int
 */
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"


int ** jumpHorsePuzzle (int n);
int ** createMatrix (int m, int n);
int    canJump (int ** board,int l,int c,int mov,int n);
void   jumpHorse (int * hl, int * hc, int mov);
void   jumpbackHorse (int * hl, int * hc, int mov);

int main(int argc, char const *argv[])
{
	int n,i,j;
	int **board;

	printf("Input the n: ");
	scanf("%d",&n);
	board = jumpHorsePuzzle(n);
	printf("--------------------------------------BOARD----------------------------\n");
	for (i = 0; i < n; i++){
		for (j = 0; j < n; j++)
			printf("%02d ",board[i][j]);
		printf("\n");
	}

	
	return 0;
}

int ** createMatrix(int m, int n)
{
	int ** A;
	int i,j;
	A = malloc(m * sizeof(int*));
	if (A != NULL)
		for (i = 0; i < n; i++)
			A[i] = malloc(n * sizeof(int));

	/*Fill matrix with zeroes */
	for(i = 0;i < m;i++)
		for (j = 0;j < n; j++)			
			A[i][j] = 0;
	return A;
}



void   jumpbackHorse (int * hl, int * hc, int mov) { 
	switch(mov) {
		case 1:
			*hl += 1;
			*hc -= 2;		
			break;		
		case 2:
			*hl += 2;
			*hc -= 1;
			break;
		case 3:
			*hl += 2;
			*hc += 1;
			break;
		case 4:
			*hl += 1;
			*hc += 2;
			break;
		case 5:
			*hl -= 1;
			*hc += 2;
			break;
		case 6:
			*hl -= 2;
			*hc += 1;
			break;
		case 7:
			*hl -= 2;
			*hc -= 1;
			break;	
		case 8:
			*hl -= 1;
			*hc -= 2;
			break;
	}
}

void   jumpHorse (int * hl, int * hc, int mov) { 
	switch(mov) {
		case 1:
			*hl -= 1;
			*hc += 2;		
			break;		
		case 2:
			*hl -= 2;
			*hc += 1;
			break;
		case 3:
			*hl -= 2;
			*hc -= 1;
			break;
		case 4:
			*hl -= 1;
			*hc -= 2;
			break;
		case 5:
			*hl += 1;
			*hc -= 2;
			break;
		case 6:
			*hl += 2;
			*hc -= 1;
			break;
		case 7:
			*hl += 2;
			*hc += 1;
			break;	
		case 8:
			*hl += 1;
			*hc += 2;
			break;
	}
}
int canJump (int ** board,int l,int c,int mov,int n) {
	/*	    HOW MOVEMENT WORKS 
	 *			  x___x
	 *		  x_____|_____x
	 *			    |
	 *				|
	 *				H
	 *				|
	 *		   x____|____x
	 *				|
	 *			  x___x
	 * OBS:  A total of eight different movements
	 */

	switch(mov) {
		case 1:			
			if (l > 0 && c < n - 2 	   && board[l-1][c+2] == 0)
				return 1;
			break;
		case 2:
			if (l > 1 && c < n - 1 	   && board[l-2][c+1] == 0)
				return 1;
				break;			
		case 3:
			if (l > 1 && c > 0     	   && board[l-2][c-1] == 0)
				return 1;
			break;
		case 4:
			if (l > 0 && c > 1    	   && board[l-1][c-2] == 0)
				return 1;
			break;
		case 5:
			if (l < n - 1 && c > 1 	   && board[l+1][c-2] == 0)
				return 1;
			break;
		case 6:
			if (l < n - 2 && c > 0 	   && board[l+2][c-1] == 0)
				return 1;
			break;
		case 7:
			if (l < n - 2 && c < n - 1 && board[l+2][c+1] == 0)
				return 1;
			break;
		case 8:
			if (l < n - 1 && c < n - 2 && board[l+1][c+2] == 0)
				return 1;
			break;
		
	}
	return 0;
}




int ** jumpHorsePuzzle (int n)
{
	/*Print a solution to the jump horse puzzle in a n x n board if it exists */

	int horL,horC,mov,jmp, ok;
	int ** board;
	stack * mem;

	board = createMatrix(n,n);
	mem   = newStack(n*n);
	/*The horse starts in [0][0] */	
	horL  = horC = n - 1;
	board[horL][horC] = 1;
	jmp   = 2;
	mov   = 1;

	while (jmp <= n*n) {		
		ok = 0;
		while (mov <= 8 && ok == 0) 
			if (canJump(board,horL,horC,mov,n))				
				ok = 1;			
			else
				mov++;
		if (ok == 1) {
			push(mem,mov);
			jumpHorse(&horL,&horC,mov);
			board[horL][horC] = jmp;
			jmp++;
			mov = 1;
		}
		else { 
			/* Backtracking */
			if (isEmpty(*mem)) { 
				printf("There's no solution!\n");
				return ;
			}
			mov = pop(mem);
			board[horL][horC] = 0;
			jmp--;
			jumpbackHorse(&horL,&horC,mov);
			mov++;
		}
	}
	return board;

}