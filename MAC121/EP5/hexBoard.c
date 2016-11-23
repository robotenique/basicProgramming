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

/* Retorna um array com is ID's dos 6 vizinhos de um Hexágono */
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
    int n, *neighbors;
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

getHexTopLeftN(int id, HexBoard *board) {
    if(!isHexagonValid(id, board))
        return -1;
    
}
getHexTopRightN(int id, HexBoard *board) {
    if(!isHexagonValid(id, board))
        return -1;
    
}
getHexLeftN(int id, HexBoard *board) {
    if(!isHexagonValid(id, board))
        return -1;
    
}
getHexRightN(int id, HexBoard *board) {
    if(!isHexagonValid(id, board))
        return -1;
    
}
getHexBotLeftN(int id, HexBoard *board) {
    if(!isHexagonValid(id, board))
        return -1;
    
}
getHexBotRightN(int id, HexBoard *board) {
    if(!isHexagonValid(id, board))
        return -1;
    
}

int * hexgrid_getCellNeighbors(int id, HexGrid * hexgrid) {


    int n = hexgrid_getCellNeighborsNumber(id, hexgrid);

    int * neighbors = malloc(sizeof(int)*n);

    if(isHexTopBorder(id, hexgrid)==0 &&
    hexgrid_isCellRightBorder(id, hexgrid)==0 &&
    hexgrid_isCellBotBorder(id, hexgrid)==0 &&
    hexgrid_isCellLeftBorder(id, hexgrid)==0) {
        // I have 6 neighbor max - I am a normal cell
        neighbors[0] = hexgrid_getCellTopLeftNeighbor(id, hexgrid);
        neighbors[1] = hexgrid_getCellTopRightNeighbor(id, hexgrid);
        neighbors[2] = hexgrid_getCellLeftNeighbor(id, hexgrid);
        neighbors[3] = hexgrid_getCellRightNeighbor(id, hexgrid);
        neighbors[4] = hexgrid_getCellBotLeftNeighbor(id, hexgrid);
        neighbors[5] = hexgrid_getCellBotRightNeighbor(id, hexgrid);
    } else {
        // I have a lot of neighbors - I am a border cell
        int i, j;

        if(hexgrid_isCellTopBorder(id, hexgrid)==1) {
            // I'm the top border
            for(i=0; i<hexgrid->size; i++) {
                neighbors[i] = i;
            }
        } else if(hexgrid_isCellBotBorder(id, hexgrid)==1) {
            // I'm the bot border
            for(i=0, j=hexgrid->size*hexgrid->size-hexgrid->size; j<hexgrid->size*hexgrid->size; i++, j++) {
                neighbors[i] = j;
            }
        } else if(hexgrid_isCellLeftBorder(id, hexgrid)==1) {
            // I'm the left border
            for(i=0, j=0; j<=hexgrid->size*hexgrid->size-hexgrid->size; i++, j=j+hexgrid->size) {
                neighbors[i] = j;
            }
        } else if(hexgrid_isCellRightBorder(id, hexgrid)==1) {
            // I'm the right border
            for(i=0, j=hexgrid->size-1; j<hexgrid->size*hexgrid->size; i++, j=j+hexgrid->size) {
                neighbors[i] = j;
            }
        }
    }

    return neighbors;
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
































x
