#ifndef _GAME_H_
#define _GAME_H_
#include "hexBoard.h"
#include "hexTypes.h"

void gameLoop(HexBoard *board, color myPlayer);
color checkVictory(HexBoard *board);
int getOponentMove(HexBoard *board, color p2);

#endif
