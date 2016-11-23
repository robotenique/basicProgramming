#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hexBoard.h"
#include "hexTypes.h"
#include "game.h"

/* TODO: remove unused functions */
void printUsage(bool gameIsOn);

int main(int argc, char const *argv[]) {
    bool gameIsOn;
    bool debug;
    color myPlayer;
    HexBoard *board;
    gameIsOn = debug = false;

    /* Initial input verification */
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

    /* Assertion = gameIsOn = true, debug = (true || false) */

    board = newHexBoard(N_SIZE);
    if(myPlayer == BLACK) {
        /* Read the move from the stdin, and update the Board*/
        /* scanf(x,x), updtBoard() */
        /* TODO: consider pie rule */
    }

    /* Start the loop */
    gameLoop(board, myPlayer);
    return 0;
}



void printUsage(bool gameIsOn) {
    if(gameIsOn)
    printf("Usage: <row> <column> \n");
    else
        printf("Usage: ./ep5 <pegColor(p, b)> [d]\n");
    exit(EXIT_SUCCESS);
}
