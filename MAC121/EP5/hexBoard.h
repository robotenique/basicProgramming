#ifndef _HEX_BOARD_H_
#define _HEX_BOARD_H_
#include "hexTypes.h"

HexBoard *newHexBoard( s_Int size);
void destroyHexBoard(HexBoard *board);

/* Funções dos hexágonos */
bool isHexagonValid(int id, HexBoard *board);
int getHexagonsCount(HexBoard *board);
color getHexagonColor(int id, HexBoard *board);
void setHexagonColor(int id, HexBoard *board, color color);
int *getHexagonNeighbors(int id, HexBoard *board);
int getHexagonNeighborC(int id, HexBoard *board);

/* Border verification functions */
bool isHexNearTopBorder(int id, HexBoard *board);
bool isHexNearBotBorder(int id, HexBoard *board);
bool isHexNearLeftBorder(int id, HexBoard *board);
bool isHexNearRightBorder(int id, HexBoard *board);
bool isHexTopBorder(int id, HexBoard *board);
bool isHexBotBorder(int id, HexBoard *board);
bool isHexLeftBorder(int id, HexBoard *board);
bool isHexRightBorder(int id, HexBoard *board);

/* Get neighbors functions */
int getHexTopLeftN(int id, HexBoard *board);
int getHexTopRightN(int id, HexBoard *board);
int getHexLeftN(int id, HexBoard *board);
int getHexRightN(int id, HexBoard *board);
int getHexBotLeftN(int id, HexBoard *board);
int getHexBotRightN(int id, HexBoard *board);

/* Get borders function */
int boardGetLeftBorder(HexBoard *board);
int boardGetTopBorder(HexBoard *board);
int boardGetRightBorder(HexBoard *board);
int boardGetBotBorder(HexBoard *board);

/* Funções auxiliares */
void boardPrint(HexBoard *board);

#endif
