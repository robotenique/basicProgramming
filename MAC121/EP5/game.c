#include <stdio.h>
#include <time.h>
#include "game.h"
#include "pathFind.h"
#include "hexAI.h"
#define MAX_DEPTH 4

color gamePlay(HexBoard *board, color player);
int gameDecide(HexBoard *board, color player, int maxDepth);


void gameLoop(HexBoard *board, color myPlayer) {
    int p2Move;
    color winner, p2;
    winner = NONE;
    if(myPlayer == WHITE)
        p2 = BLACK;
    else
        p2 = WHITE;
    /* Play the game until one of the player wins */
    for(;;) {
        if(board->player == myPlayer) {
            /* Faz um movimento */
            winner = gamePlay(board, myPlayer);
            /* Verifica se houve vencedor */
            if(winner != NONE) {
                printf("%c ganhou\n",(winner == WHITE) ? 'b' : 'p');
                return;
            }
        }
        fflush(stdin);
        p2Move = getOponentMove(board, p2);
        if(board->turnN == 2 && board->hexs[p2Move].color != NONE &&
           myPlayer == WHITE) {
            /* Foi usada a pieRule pelo player2 */
            p2 = WHITE;
            myPlayer = BLACK;
        }
        else {
            setHexagonColor(p2Move, board, p2);
            if(board->player == WHITE)
                board->player = BLACK;
            else
                board->player = WHITE;
        }
        board->turnN++;
    }
}


color gamePlay(HexBoard *board, color player) {
    int move;
    color winner = checkVictory(board);
    if(winner == WHITE || winner == BLACK)
        return winner;
    move = gameDecide(board, player, MAX_DEPTH);
    setHexagonColor(move, board, player);
    board->turnN++;
    if(board->player == WHITE)
        board->player = BLACK;
    else
        board->player = WHITE;

    printf("%d %d\n",move%board->size,move/board->size);
    boardPrint(board);
    return NONE;
}

int gameDecide(HexBoard *board, color player, int maxDepth) {
    int bestM, arand, i, j;
    HexBoard *dup;
    bestM = -1;
    if(board->turnN < 3) {
        /* Tenta pegar uma posição em quadrantes diferentes */
        if(player == WHITE && board->turnN == 1) {
            do {
                i = (rand()%1000)%4;
                j = (rand()%1000)%(4 - i);
                if((rand()%1000)%2 < 1) {
                    i = board->size - 1 - i;
                    j = board->size - 1 - j;
                }
                bestM = j*board->size + i;
            } while(!isHexagonPlayable(bestM, board));
            return bestM;
        }
        else if(player == BLACK) {
            do {
                bestM = board->size*board->size/2;
            } while(!isHexagonPlayable(bestM, board));
            return bestM;
        }
    }
    arand = rand()%1000;
    /* Coloca um pouco de aleatoriedade no jogo :)  */
    if(arand < 50) {
        bestM = (int)(board->size*board->size*(rand()/(1.0 + RAND_MAX)));
        while(!isHexagonPlayable(bestM, board))
            bestM = (int)(board->size*board->size*(rand()/(1.0 + RAND_MAX)));
        return bestM;
    }
    dup = cloneHexBoard(board);
    MTDfRun(dup, player, maxDepth, &bestM);
    destroyHexBoard(dup);

    if(!isHexagonPlayable(bestM, board))
        exit(EXIT_FAILURE);
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
            (isHexagonPlayable(id, board) != 1 && board->turnN != 2));
    return id;
}
