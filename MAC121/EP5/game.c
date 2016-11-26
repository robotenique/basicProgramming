#include <stdio.h>
#include <time.h>
#include "game.h"
#include "pathFind.h"
#include "hexAI.h"
#define MAX_DEPTH 4

color gamePlay(HexBoard *board, color player);
int gameDecide(HexBoard *board, color player, int maxDepth);
int getOponentMove(HexBoard *board, color p2);

void gameLoop(HexBoard *board, color myPlayer) {
    color winner, p2;
    winner = NONE;
    if(myPlayer == WHITE)
        p2 = BLACK;
    else
        p2 = WHITE;
    printf("TENTANDO 1ª JOGADA...\n");
    /* Play the game until one of the player wins */
    for(;;) {
        /* Make a move */
        winner = gamePlay(board, myPlayer);
        /* Check if we won */
        if(winner != NONE) {
            printf("%c ganhou\n",(winner == WHITE) ? 'b' : 'p');
            return;
        }
        fflush(stdin);
        setHexagonColor(getOponentMove(board, p2), board, p2);

        /* TODO: REMOVE */
        /* TODO: remind to read the PLAY from the STDIN, And then
         * update the board. We do not need to call 'gamePlay' again
         * BElow, the move is read from the STDIN.
         */
        /* Make a move with the other player */
        /* Check if player2 won */

    }
}


color gamePlay(HexBoard *board, color player) {
    color winner = checkVictory(board);
    if(winner == WHITE || winner == BLACK)
        return winner;

    setHexagonColor(gameDecide(board, player, MAX_DEPTH), board, player);
    board->turnN++;
    if(board->player == WHITE)
        board->player = BLACK;
    else
        board->player = WHITE;

    boardPrint(board);
    return NONE;
}

int gameDecide(HexBoard *board, color player, int maxDepth) {
    int bestM, arand;
    HexBoard *dup;
    bestM = -1;
    if(board->turnN < 2) {
        srand(time(NULL));

        if(player != WHITE)
            bestM = board->size*board->size/2;
        else
            bestM = (int)(board->size*board->size*(rand()/(1.0 + RAND_MAX)));

        while(!isHexagonPlayable(bestM, board))
            bestM = (int) (board->size*board->size*(rand()/(1.0 + RAND_MAX)));
        return bestM;
    }
    arand = rand()%1000;
    if(arand < 100) {
        bestM = (int)(board->size*board->size*(rand()/(1.0 + RAND_MAX)));
        while(!isHexagonPlayable(bestM, board))
            bestM = (int)(board->size*board->size*(rand()/(1.0 + RAND_MAX)));
        return bestM;
    }
    dup = cloneHexBoard(board);
    MTDfRun(dup, player, maxDepth, &bestM);
    destroyHexBoard(dup);
    if(!isHexagonPlayable(bestM, board)){
        printf("BUGOU LEGALLL\n"); /* TODO REMOVE */
        exit(EXIT_FAILURE);
    }
    return bestM;
}

color checkVictory(HexBoard *board) {
    DjkStorage *djkS;
    DjkPath *djkPath;
    color winner;
    winner = NONE;
    /* Verificando condições de vitória */
    djkS = dijkstra(board, boardGetTopBorder(board), boardGetBotBorder(board),
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

int getOponentMove(HexBoard *board, color p2) {
    int x, y, id;
    do {
    scanf("%d %d", &x, &y);
    id = y*N_SIZE + x;
    }
    while ( y > 13 || x > 13 || y < 0 || x < 0 ||
            !isHexagonValid(id, board) ||
            isHexagonPlayable(id, board) != 1);
    return id;
}
