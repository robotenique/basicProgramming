#include <stdio.h>
#include "game.h"
/* TODO: Define a max-depth recursion size (in the gamePlay function)?? */
color gamePlay(HexBoard *board, color player);
color checkVictory(HexBoard *board);
void printVictory(color winner);

void gameLoop(HexBoard *board, color myPlayer) {
    color winner;
    winner = NONE;
    /* Play the game until one of the player wins */
    for(;;) {
        /* Make a move */
        winner = gamePlay(board, myPlayer);
        /* Check if we won */
        if(winner != NONE) {
            printf("%c ganhou\n",(winner == WHITE) ? 'b' : 'p');
            return;
        }
        /* TODO: remind to read the PLAY from the STDIN! */
        /* Make a move with the other player */
        winner = gamePlay(board, myPlayer);
        /* Check if player2 won */
        if(winner) {
            printf("%c ganhou\n",(winner == WHITE) ? 'b' : 'p');
            return;
        }
    }
}

color gamePlay(HexBoard *board, color player) {
    color winner = checkVictory(board);
    if(winner == WHITE || winner == BLACK) {
        return winner;
    }

    return NONE;

}

color checkVictory(HexBoard *board) {
    /* Verificando condições de vitória */
    DjkStorage *djkS;
    DjkPath *djkPath;
    color winner;

    winner = NONE;
}
int hex_game_checkVictory(HexGrid * grid) {
	// Verify Victory Conditions
	DijkstraResult * dres;
	DijkstraPath * dpath;

	int victory = BLANK;

	dres = dijkstra(grid, hexgrid_getTopBorder(grid), hexgrid_getBotBorder(grid), 0x04, 1, 1, 1);
	dpath = dijkstra_getPath(dres, -1);
	if(dpath->length>0) {
		victory = BLACK;
	}
	dijkstra_destroyPath(dpath);
	dijkstra_destroy(dres);

	dres = dijkstra(grid, hexgrid_getRightBorder(grid), hexgrid_getLeftBorder(grid), 0x02, 1, 1, 1);
	dpath = dijkstra_getPath(dres, -1);
	if(dpath->length>0) {
		victory = WHITE;
	}
	dijkstra_destroyPath(dpath);
	dijkstra_destroy(dres);

	return victory;
}
