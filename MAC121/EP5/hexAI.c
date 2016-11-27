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

    while(lowerbound < upperbound) {
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

    return g;
}
/*
 * Function: MTDfRun
 * --------------------------------------------------------
 * Executa o algoritmo MTDf usando a depth máxima especificada.
 *
 * @args    board: O tabuleiro do jogo
 *          player: A cor do jogador
 *          maxDepth: A profundidade máxima para executar o algoritmo
 *          bestMove: ponteiro para a melhor jogada
 *
 * @return O ID do hexágono que representa a melhor jogada calculada pelo
 *         algoritmo
 */
int MTDfRun(HexBoard *board, color player, int maxDepth, int *bestMove) {
    int bValue, d;
    HashTable *transTable;
    bValue = 0;
    /* Cria a transposition table que vai armazenar os tabuleiros */
    transTable = HashTableCreate(HASH_LIM);
    HashTableSetHashFunction(transTable, HashTableStringHashFunction);
    HashTableSetDeallocationFunctions(transTable, free, free);
    HashTableSetKeyComparisonFunction(transTable, abKeyCmp);

    t = clock(); /* Usado para controle de tempo */
    /* Executa até o depth máximo */
    for(d = 1; d <= maxDepth; d++)
        bValue = MTDfAlgorithm(board, bValue, d, player, transTable, bestMove);

    HashTableDestroy(transTable);
    return bValue;

}
