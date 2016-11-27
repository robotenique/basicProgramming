#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include "error.h"
#include "hexBoard.h"
#include "hexTypes.h"
#include "pathFind.h"
#include "game.h"

/* TODO: remove unused functions */
void printUsage(bool gameIsOn);

int main(int argc, char const *argv[]) {
    int piePos, i, j;
    bool applyPie, gameIsOn;
    color myPlayer;
    HexBoard *board;

    gameIsOn = false;
    debug = false;
    srand(time(NULL));

    /* Verificação da entrada */
    if(argc < 2 || argc > 3) {
        printUsage(gameIsOn);
    }
    if(argc == 2) {
        if(strcmp(argv[1],"p") == 0)
            myPlayer = BLACK;
        else if(strcmp(argv[1],"b") == 0)
            myPlayer = WHITE;
        else
            printUsage(gameIsOn);
        gameIsOn = true;

    }
    else if(argc == 3) {
        if(strcmp(argv[1],"p") == 0)
            myPlayer = BLACK;
        else if(strcmp(argv[1],"b") == 0)
            myPlayer = WHITE;
        else
            printUsage(gameIsOn);
        if(strcmp(argv[2],"d") == 0)
            debug = true;
        else
            printUsage(gameIsOn);
        gameIsOn = true;
    }


    board = newHexBoard(N_SIZE);
    if(myPlayer == BLACK) {
        piePos = getOponentMove(board, WHITE);
        i = piePos%board->size;
        j = piePos/board->size;
        applyPie = false;
        if(i > 3 && i < 10 && j > 3 && j < 10)
            applyPie = true;
        else if((i < 5 && j < 5) || (i > 8 && j > 8))
            applyPie = true;
        if(applyPie) {
            myPlayer = WHITE;
            printf("%d %d\n",piePos%board->size,piePos/board->size);
        }
        setHexagonColor(piePos, board, WHITE);
        board->turnN++;
        if(board->player == WHITE)
            board->player = BLACK;
        else
            board->player = WHITE;
        boardPrint(board);
    }
    /* Start the loop*/
    gameLoop(board, myPlayer);
    destroyHexBoard(board);

    return 0;
}



void printUsage(bool gameIsOn) {
    if(gameIsOn)
    printf("Usage: <row> <column> \n");
    else
        printf("Usage: ./ep5 <pegColor(p, b)> [d]\n");
    exit(EXIT_SUCCESS);
}
