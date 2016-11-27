#include <stdlib.h>
#include <stdio.h>
#include "error.h"
#include "hexBoard.h"
int getBoardStrLength(HexBoard *board);

HexBoard *newHexBoard( s_Int size) {
    int i;
    HexBoard *board = emalloc(sizeof(HexBoard));
    board->size = size;
    board->player = WHITE;
    board->hexs = emalloc(sizeof(Hexagon) *(size*size + 4));
    board->turnN = 1;
    for(i = 0; i < size*size; board->hexs[i].color = NONE, i++);

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

HexBoard *cloneHexBoard(HexBoard *board) {
    int i;

    HexBoard *h = emalloc(sizeof(HexBoard));
    h->size = board->size;
    h->turnN = board->turnN;
    h->player = board->player;
    h->hexs = emalloc(sizeof(HexBoard)*(h->size*h->size+4));

    for(i = 0; i < h->size*h->size+4; i++)
        h->hexs[i].color = board->hexs[i].color;


    return h;

}

/* Retorna uma representação em texto da HexBoard
 * (Sem as bordas)
 */
char *stringfyBoard(HexBoard *board) {
    int i;
    char *str;
    str = emalloc(getBoardStrLength(board)*sizeof(char) + 1);
    for(i = 0; i < getHexagonsCount(board); i++) {
        str[i] = '0' + board->hexs[i].color;
    }
    str[i] = '\0';
    return str;
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

int isHexagonPlayable(int id, HexBoard *board) {
    if(!isHexagonValid(id, board))
        return -1;
    if(board->hexs[id].color == NONE)
        return 1;
    else
        return 0;
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

bool isHexTopBorder(int id,HexBoard *board) {
    if(id == board->size*board->size)
        return true;
    return false;
}

bool isHexBotBorder(int id,HexBoard *board) {
    if(id == board->size*board->size+2)
        return true;
    return false;
}

bool isHexLeftBorder(int id,HexBoard *board) {
    if(id == board->size*board->size+3)
        return true;
    return false;
}

bool isHexRightBorder(int id,HexBoard *board) {
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

    return id + board->size-1;
}

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
        return board->size;
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

void setHexagonColor(int id, HexBoard *board, color color) {
    if(!isHexagonValid(id, board))
        return;
    if(color != WHITE && color != BLACK && color != NONE)
        return;
    board->hexs[id].color = color;
}

char getBoardChar(int c) {
    if(c == 1)
        return 'b';
    if(c == 2)
        return 'p';
    return '-';
}
void boardPrint(HexBoard *board) {
    int i, j, k, len;
    char **list;
    if(!debug) return;
    len = board->size;
    list = emalloc(sizeof(char*)*len);
    for(i = 0; i < len; i++)
        list[i] = emalloc(sizeof(char)*len);
    for(i = 0; i < len; i++)
        for(j = 0; j < len; j++)
            list[i][j] = 0;
    for(i = 0;i < len; i++)
        for(j = 0; j < len; j++)
            list[i][j] = board->hexs[j*len + i].color;
    for(i = 0; i < len; i++){
        for(k = 0; k < i; fprintf(stderr, " "), k++);
        fprintf(stderr, "\\");
        for(j = 0;j < len;j++)
            fprintf(stderr, "%c ",getBoardChar(list[i][j]));
        fprintf(stderr, "\\\n");
    }
    for(i = 0; i < len; i++)
        free(list[i]);
    free(list);
}


bool isHexNearTopBorder(int id, HexBoard *board) {
    if(!isHexagonValid(id, board)) return -1;
    if(id >= 0 && id < board->size)
        return 1;
    else
        return 0;
}

bool isHexNearBotBorder(int id, HexBoard *board) {
    if(!isHexagonValid(id, board)) return -1;
    if(id >= board->size*board->size - board->size &&
       id < board->size*board->size)
         return 1;
    else
        return 0;
}

bool isHexNearLeftBorder(int id, HexBoard *board) {
    if(!isHexagonValid(id, board)) return -1;
    if((id + 1) % board->size == 1)
        return 1;
    else
        return 0;
}

bool isHexNearRightBorder(int id, HexBoard *board) {
    if(!isHexagonValid(id, board)) return -1;
    if((id + 1) % board->size == 0)
        return 1;
    else
        return 0;
}

int getBoardStrLength(HexBoard * board) {
    return getHexagonsCount(board);
}

void bPrint2(HexBoard * board, char * extra) {
    int i, j;

    fprintf(stderr, "\\ ");

    for(i=0; i<board->size*board->size; i++) {
        if(i%board->size==0 && i>0) {
            fprintf(stderr, "\\\n");

            for(j=0; j<i/board->size; j++) {
                fprintf(stderr, " ");
            }

            fprintf(stderr, "\\ ");
        }

        if(extra!=NULL && extra[i]!=0) {
            fprintf(stderr, "%c ", extra[i]);
        } else if(board->hexs[i].color==BLACK) {
            fprintf(stderr, "p ");
        } else if(board->hexs[i].color==WHITE){
            fprintf(stderr, "b ");
        } else {
            fprintf(stderr, "- ");
        }
    }

    fprintf(stderr, "\\\n");
    fflush(stderr);

}
