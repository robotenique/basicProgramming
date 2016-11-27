#ifndef __HEX_AI_ALPHA_BETA_H__
#define __HEX_AI_ALPHA_BETA_H__
#include <time.h>
#include "hashTable.h"
#include "hexBoard.h"
#define MIN 0
#define MAX 1
clock_t t;

/* Uma entry da Transposition Table */
typedef struct {
	int score;
	int type;
	int depth;
} transTEntry;

int alphaBetaAlgorithm(HexBoard * board, int alpha, int beta, int depth,
    int maxDepth, color player, char type, HashTable *transTable, int *bestM);

int abKeyCmp(const void *a, const void *b);

#endif
