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

int getHexagonsCount(HexBoard *board) {
    return board->size*board->size + 4;
}

bool isHexagonValid(int id, HexBoard *board) {
    if(id >= 0 && id < getHexagonsCount(board))
        return true;
     else
        return false;
}

/* Check if a given Hexagon is not a border Hexagon */
bool isHexagonSimple(int id, HexBoard *board) {
    if(id >= 0 && id <= getHexagonsCount(board) - 4)
        return true;
    else
        return false;
}

color getHexagonColor(int id, HexBoard *board) {
    if(!isHexagonValid(id, board)) return INVALID;
    return board->hexs[id].color;
}

/* Retorna um array com os ID's dos 6 vizinhos de um Hexágono */
/* Ordem dos vizinhos:
 *
 *                 _____
 *                /     \
 *          _____/   3   \_____
 *         /     \       /     \
 *        /   5   \_____/   1   \
 *        \       /     \       /
 *         \_____/  ID   \_____/
 *         /     \       /     \
 *        /   6   \_____/   2   \
 *        \       /     \       /
 *         \_____/   4   \_____/
 *               \       /
 *                \_____/
 */
int *getHexagonNeighbors(int id, HexBoard *board) {
    int n, i, j, aux, *neighbors;
    if(!isHexagonValid(id, board))
        return NULL;

    n = getHexagonNeighborC(id,  board);

    neighbors = emalloc(sizeof(int)*n);

    if(!isHexTopBorder(id, board)  && !isHexBotBorder(id, board) &&
       !isHexLeftBorder(id, board) && !isHexRightBorder(id, board)) {
        /* Hexágono comum, 6 vizinhos */
        neighbors[0] = getHexTopLeftN(id, board);
        neighbors[1] = getHexTopRightN(id, board);
        neighbors[2] = getHexLeftN(id, board);
        neighbors[3] = getHexRightN(id, board);
        neighbors[4] = getHexBotLeftN(id, board);
        neighbors[5] = getHexBotRightN(id, board);

    }
    else {
        /* Hexágono está na borda */
        if(isHexTopBorder(id, board)) {
            for(i = 0; i < board->size; neighbors[i] = i, i++);
        }
        else if(isHexBotBorder(id, board)) {
            j = board->size*board->size-board->size;
            for(i = 0; j < board->size*board->size; i++, j++)
                neighbors[i] = j;
        }
        else if(isHexLeftBorder(id, board)) {
            aux = board->size*board->size-board->size;
            for(i = 0, j = 0; j <= aux; i++, j = j + board->size)
                neighbors[i] = j;
        }
        else if(isHexRightBorder(id, board)) {
            aux = board->size*board->size;
            for(i = 0, j = board->size-1; j < aux; i++, j = j + board->size)
                neighbors[i] = j;
        }
    }
    return neighbors;
}

int isHexTopBorder(int id,HexBoard *board) {
    if(id == board->size*board->size)
        return true;
    return false;
}

int isHexBotBorder(int id,HexBoard *board) {
    if(id == board->size*board->size+2)
        return true;
    return false;
}

int isHexLeftBorder(int id,HexBoard *board) {
    if(id == board->size*board->size+3)
        return true;
    return false;
}

int isHexRightBorder(int id,HexBoard *board) {
    if(id == board->size*board->size+1)
        return true;
    return false;
}

int getHexTopLeftN(int id, HexBoard *board) {
    if(!isHexagonValid(id, board))
        return -1;

    if(isHexNearTopBorder(id, board))
        return board->size*board->size;

    return id - board->size;

}

int getHexTopRightN(int id, HexBoard *board) {
    if(!isHexagonValid(id, board))
        return -1;

    if(isHexNearTopBorder(id, board))
        return board->size*board->size;

    if(isHexNearRightBorder(id, board))
        return board->size*board->size+1;

    return id - board->size+1;
}

int getHexLeftN(int id, HexBoard *board) {
    if(!isHexagonValid(id, board))
        return -1;

    if(isHexNearLeftBorder(id, board))
        return board->size*board->size+3;

    return id - 1;
}

int getHexRightN(int id, HexBoard *board) {
    if(!isHexagonValid(id, board))
        return -1;

    if(isHexNearRightBorder(id, board))
        return board->size*board->size+1;

    return id + 1;
}

int getHexBotLeftN(int id, HexBoard *board) {
    if(!isHexagonValid(id, board))
        return -1;

    if(isHexNearBotBorder(id, board))
        return board->size*board->size+2;

    if(isHexNearLeftBorder(id, board))
        return board->size*board->size+3;

    return id + hexgrid->size-1;
}

/* TODO; maybe adjust this function below to match the above... */
int getHexBotRightN(int id, HexBoard *board) {
    if(!isHexagonValid(id, board))
        return -1;

    if(isHexNearBotBorder(id, board))
        return board->size*board->size+2;

    return id + board->size;
}


/* Retorna o número de vizinhos de um hexagono.
 * Se o hexágono é invalido, retorna -1
 * Se é um hexágono comum, retorna 6,
 * Se é um hexágono da borda, retorna o valor na borda
 */
int getHexagonNeighborC(int id, HexBoard *board) {
    if(!isHexagonValid(id, board))
        return -1;
    if(id >= board->size*board->size)
        return hexgrid->size;
    else
     return 6;
 }

int boardGetLeftBorder(HexBoard *board) {
    return board->size*board->size+3;
 }

int boardGetTopBorder(HexBoard *board) {
    return board->size*board->size;
 }

int boardGetRightBorder(HexBoard *board) {
    return board->size*board->size+1;
 }

int boardGetBotBorder(HexBoard *board) {
    return board->size*board->size+2;
 }































x
