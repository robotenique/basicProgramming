#ifndef __HEX_AI_ALPHA_BETA_H__
#define __HEX_AI_ALPHA_BETA_H__
#include "hashTable.h"
#include "hexBoard.h"
#define MIN 0
#define MAX 1

long stats_mtdfRun;
long stats_evalLeaf;
long stats_cacheAccess;
long stats_newCached;
long stats_nodes;

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
