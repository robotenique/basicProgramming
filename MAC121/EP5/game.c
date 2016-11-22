#include "game.h"
/* TODO: Define a max-depth recursion size (in the gamePlay function)?? */
color gamePlay(HexBoard *board, color player);
int checkVictory(HexBoard *board);
void printVictory(color winner);

void gameLoop(HexBoard *board, color myPlayer) {
    color winner;
    char player1;
    char player2;
    isSolved = NONE;
    /* Play the game until one of the player wins */
    for(;;) {
        /* Make a move */
        winner = gamePlay(*board, myPlayer);
        /* Check if we won */
        if(winner != NONE) {
            printf("%c ganhou\n",(winner == WHITE) ? 'b' : 'p');
            return;
        }
        /* TODO: remind to read the PLAY from the STDIN! */
        /* Make a move with the other player */
        winner = gamePlay(*board, myPlayer);
        /* Check if player2 won */
        if(winner) {
            printf("%c ganhou\n",(winner == WHITE) ? 'b' : 'p');
            return;
        }
    }
}

void printVictory(color winner) {
}
color gamePlay(HexBoard *board, color player) {
    color winner = checkVictory(board);
    if(winner == WHITE || winner == BLACK) {
        return winner;
    }

    return NONE;


	// Is it my turn ?
	if(grid->turn_player!=player) {
		printf("It's not my turn ...\n");
		hexgrid_destroy(grid);
		return 0;
	}

	// Decide & Play !
	hexgrid_setCellColor(hex_game_decide(grid, player, useRandom, useABSearch, useMTDf, maxDepth), grid, player);

	grid->turn_nb++;
	if(grid->turn_player==WHITE) {
		grid->turn_player=BLACK;
	} else {
		grid->turn_player=WHITE;
	}

	// Save the grid
	hexgrid_save(path, grid);

	// Print the grid
	hexgrid_print(grid, NULL);

	// Destroy the grid
	hexgrid_destroy(grid);

	return 1;
}
