#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "hexBoard.h"
#include "hexTypes.h"
#include "pathFind.h"
#include "game.h"

/* TODO: remove unused functions */
void printUsage(bool gameIsOn);

int main(int argc, char const *argv[]) {
    bool gameIsOn;
    color myPlayer;
    HexBoard *board;
    gameIsOn = debug = false;

    /* Initial input verification */
    /*
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
    }*/
    myPlayer = WHITE;
    gameIsOn = true;
    debug = false;


    /* Assertion = gameIsOn = true, debug = (true || false) */

    board = newHexBoard(N_SIZE);
    if(myPlayer == BLACK) {
        /* Read the move from the stdin, and update the Board*/
        /* scanf(x,x), updtBoard() */
        /* TODO: consider pie rule */
    }

    /* Start the loop*/
    gameLoop(board, myPlayer);
    /*
    board = newHexBoard(4);
    printf("BOARD - STATE 0\n");
    boardPrint(board);
    setHexagonColor(3, board, BLACK);
    setHexagonColor(6, board, BLACK);
    setHexagonColor(9, board, BLACK);
    setHexagonColor(12, board, BLACK);
    printf("BOARD - STATE 1\n");
    boardPrint(board);
    printf("DIJKSTRA ATE Nº 18\n");
    res = dijkstra(board, 16, 18, 0x04, 1, 1, 1);
    path = djkGetPath(res, -1);
    assert(path->length==5);
    assert(path->path[0]==3);
    assert(path->path[1]==6);
    assert(path->path[2]==9);
    assert(path->path[3]==12);
    assert(path->path[4]==18);
    printPath(path);
    djkDestroyPath(path);
    djkDestroy(res);
printf("---DIJKSTRA 100%%---\n");
    res = dijkstra(board, 16, -1, 0x04, 1, 1, 1);
    path = djkGetPath(res, -1);
    assert(path==NULL);
    path = djkGetPath(res, 18);
    assert(path->length==5);
    assert(path->path[0]==3);
    assert(path->path[1]==6);
    assert(path->path[2]==9);
    assert(path->path[3]==12);
    assert(path->path[4]==18);
    printPath(path);
    djkDestroyPath(path);
    djkDestroy(res);

    printf("Teste de cores\n");
    setHexagonColor(6, board, WHITE);
    res = dijkstra(board, 16, 18, 0x04, 1, 1, 1);
    path = djkGetPath(res, -1);
    assert(path->length==-1);
    printPath(path);
    djkDestroyPath(path);
    djkDestroy(res);

    res = dijkstra(board, 16, 18, 0x06, 1, 1, 1);
    path = djkGetPath(res, -1);
    assert(path->length==5);
    printPath(path);
    djkDestroyPath(path);
    djkDestroy(res);

    destroyHexBoard(board);

    printf("-->Deu tudo OKEI !\n");*/

    return 0;
}



void printUsage(bool gameIsOn) {
    if(gameIsOn)
    printf("Usage: <row> <column> \n");
    else
        printf("Usage: ./ep5 <pegColor(p, b)> [d]\n");
    exit(EXIT_SUCCESS);
}
