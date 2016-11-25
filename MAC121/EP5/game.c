#include <stdio.h>
#include "game.h"
#include "pathFind.h"
#include "hexAI.h"
#define MAX_DEPTH 4

color gamePlay(HexBoard *board, color player);
color checkVictory(HexBoard *board);
int gameDecide(HexBoard *board, color player, int maxDepth);

void gameLoop(HexBoard *board, color myPlayer) {
    color winner;
    winner = NONE;
    boardPrint(board);
    exit(EXIT_SUCCESS);
    /* Play the game until one of the player wins */
    for(;;) {
        /* Make a move */
        winner = gamePlay(board, myPlayer);
        /* Check if we won */
        if(winner != NONE) {
            printf("%c ganhou\n",(winner == WHITE) ? 'b' : 'p');
            return;
        }
        /* TODO: remind to read the PLAY from the STDIN, And then
         * update the board. We do not need to call 'gamePlay' again
         * BElow, the move is read from the STDIN.
         */
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

    if(winner == WHITE || winner == BLACK)
        return winner;

    /*setHexagonColor(gameDecide(board, player, MAX_DEPTH), board, player); */

    /* TODO: finish this function */

    return NONE;


}

int gameDecide(HexBoard *board, color player, int maxDepth) {
    int bestM;
    bestM = -1;
    HexBoard *dup = cloneHexBoard(board);
    MTDfAlgorithm(dup, player, maxDepth, &bestM);

}

color checkVictory(HexBoard *board) {
    DjkStorage *djkS;
    DjkPath *djkPath;
    color winner;
    winner = NONE;
    /* TODO: invert the colors here, white <==> black, and adjust c_mask correspondly*/
    /* Verificando condições de vitória */
    djkS = dijkstra(board, boardGetTopBorder(board), boardGetLeftBorder(board),
                    0x04, 1, 1, 1);
    djkPath = djkGetPath(djkS, -1);
    if(djkPath->length > 0)
        winner = BLACK;
    djkDestroyPath(djkPath);
    djkDestroy(djkS);

    djkS = dijkstra(board, boardGetRightBorder(board), boardGetLeftBorder(board),
                    0x02, 1, 1, 1);
    djkPath = djkGetPath(djkS, -1);
    if(djkPath->length > 0)
        winner = WHITE;
    djkDestroyPath(djkPath);
    djkDestroy(djkS);

    return winner;
}
