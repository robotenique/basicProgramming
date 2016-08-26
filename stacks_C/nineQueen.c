/*
 * 9 queens puzzle :  Backtrack 
 * IMPORTANT: THE STACK FILE NEED TO BE CHANGED TO THE APPRIATE TYPE.
 * ---->TYPE TO CHANGE =  int
 */

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
int posIsFree (int ** board, int r, int c, int n);
int nQueens (int n);
int ** createMatrix(m,n);

int main(int argc, char const *argv[])
{
	
	return 0;
}

int ** createMatrix(m,n)
{
	int ** A;
	int i;
	A = malloc(m * sizeof(int));
	if (A != NULL)
		for (i = 0; i < n; i++)
			A[i] = malloc(n * sizeof(int));

	return A;
}

int posIsFree (int ** board, int r, int c, int n)
{
	int i,j;
	/*Checking in line */
	for (i = 0; i < n; i++)
		if (board[r][i] == 1)
			return 0;
	/*Checking in column */
	for (i = 0; i < n; i++)
		if (board[i][c] == 1)
			return 0;
	/*Checking in diagonal*/
	/* FORWARD CHECK  */
	for (i = r, j = c; i < n && j < n; i++,j++)
		if (board[i][j] == 1)
			return 0;
	/* BACKWARD CHECK */
	for (i = r, j = c; i > 0 && j > 0; i--,j--)
		if (board[i][c] == 1)
			return 0;
	return 1;
}


int nQueens (int n)
{
	/* Print the Queens in the board if it exists */
	int curr , col, ok;
	int ** board;
	int i,j;
	stack * queens;


	board = createMatrix(n,n);
	if (board==NULL){
		printf("NOT ENOUGH MEMORY!\n");
		return ;
	}

	/*Fill matrix with zeroes */
	for(i = 0;i < n;i++)
		for (j = 0;j < n; j++)
			board[i][j] = 0;


	queens = newStack(n);
	curr   = 0;
	col    = 0;

	while(curr < n) {
		ok = 0;
		while (col < n && ok == 0) {
			if (posIsFree(board,curr,col,n))
				ok = 1;
			else
				col++;

		}
		if(ok) {
			push(queens,col);
			board[curr][col] = 1;
			curr++;
			col = 0;			
		}
		else {
			/* BACKTRACKING */
			if (isEmpty(*queens)) {
				printf("THERE'S NO SOLUTION TO THE PUZZLE!\n");
				return ;
			}
			col == pop(queens);
			curr--;
			board[cur][col] = 0;
			col++;
		}
	} 
}