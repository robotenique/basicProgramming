#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "hexAI.h"
#include "hexAI_alphaBeta.h"
#include "hashTable.h"

#define HASH_LIM 9001

int MTDfAlgorithm(HexBoard *board, int guess, int maxDepth, color player,
                 HashTable *transTable, int *bMove) {
    int g, upperbound, lowerbound, beta;
    g = guess;
    upperbound = +INT_MAX;
    lowerbound = -INT_MAX;

    stats_cacheAccess = 0;
    stats_evalLeaf = 0;
    stats_mtdfRun = 0;
    stats_newCached = 0;
    stats_nodes = 0;

    while(lowerbound < upperbound) {
        stats_mtdfRun++;
        if(g == lowerbound)
            beta = g + 1;
        else
            beta = g;

        g = alphaBetaAlgorithm(board, beta - 1, beta, 0, maxDepth, player, MAX,
                                transTable, bMove);
        if(g < beta)
            upperbound = g;
        else
            lowerbound = g;
    }
    /* Print de debug --- Estatísticas */
    printf("------Estatísticas MTDf (%ld)------\n", stats_mtdfRun);
    printf("Depth = %d\n, total de %ld nodes,  entradas no cache = %ld.\n",
            maxDepth, stats_nodes, HashTableSize(transTable));
    printf("Com %ld acessos ao cache, %ld folhas avaliadas ---> %d\n",
            stats_cacheAccess, stats_evalLeaf, g);
    return g;
}

int MTDfRun(HexBoard *board, color player, int maxDepth, int *bestMove) {
    int bValue, d;
    HashTable *transTable;
    bValue = 0;
    transTable = HashTableCreate(HASH_LIM);
    HashTableSetHashFunction(transTable, HashTableStringHashFunction);
    HashTableSetDeallocationFunctions(transTable, free, free);
    HashTableSetKeyComparisonFunction(transTable, abKeyCmp);
    printf("---- Executando MTDf ----\n");
    for(d = 1; d <= maxDepth; d++) {
        bValue = MTDfAlgorithm(board, bValue, d, player, transTable, bestMove);
    }
    printf("=> Melhor valor: %d com jogada no hexágono nº %d <=\n", bValue, *bestMove);

    HashTableDestroy(transTable);

    return bValue;

}
