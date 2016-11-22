#include <stdlib.h>
#include "error.h"
#include "hexBoard.h"

HexBoard *newHexBoard( s_Int size) {
    int i;
    HexBoard *board = emalloc(sizeof(HexBoard));
    board->size = size;
    board->player = WHITE;
    board->hexs = emalloc(sizeof(Hexagon) *(size*size + 4));
    for(i = 0; i < size*size; board->hexs[i].color = NONE, i++);
    /* TODO: Check borders colors after (see if the order is correct) */
    board->hexs[size*size].color = BLACK;
    board->hexs[size*size+1].color = WHITE;
    board->hexs[size*size+2].color = BLACK;
    board->hexs[size*size+3].color = WHITE;

    return board;
}

void destroyHexBoard(HexBoard *board) {
    free(board->hexs);
    free(board);
}
