#ifndef _HEX_BOARD_H_
#define _HEX_BOARD_H_
#include "hexTypes.h"

HexBoard *newHexBoard( s_Int size);
void destroyHexBoard(HexBoard *board);
color getHexagonColor(int id, HexBoard *board);
int getHexagonsCount(HexBoard *board);
bool isHexagonValid(int id, HexBoard *board);
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
getHexTopLeftN(int id, HexBoard *board);
getHexTopRightN(int id, HexBoard *board);
getHexLeftN(int id, HexBoard *board);
getHexRightN(int id, HexBoard *board);
getHexBotLeftN(int id, HexBoard *board);
getHexBotRightN(int id, HexBoard *board);

#endif
