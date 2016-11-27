/*
 * @author: Juliano Garcia de Oliveira
 * nº usp = 9277086
 * MAC0121
 * 28/11/2016
 * Header do algoritmo Min Max (MTDf). Mais informações em
 * https://en.wikipedia.org/wiki/MTD-f
 */
#ifndef __HEX_AI_H__
#define __HEX_AI_H__
#include "hexBoard.h"
/*
 * Function: MTDfAlgorithm
 * --------------------------------------------------------
 * Executa o algoritmo de MinMax MTDf (vêm de Memory-enhanced Test Driver with
 * node n and value f). O algoritmo minimiza e maximiza jogadas alternativas
 * usando o algoritmo alphaBeta. A Implementação deste algoritmo tem como
 * base a implementação em pseudocódigo disponível na página da Wikipedia, em
 * https://en.wikipedia.org/wiki/MTD-f
 *
 * @args    board: O tabuleiro do jogo
 *          guess: Uma jogada no tabuleiro, que será avaliada
 *          maxDepth: A profundidade máxima para executar o algoritmo
 *          player: A cor do jogador
 *          transTable: A transposition table
 *          bMove: ponteiro para a melhor jogada
 *
 * @return  O valor da melhor jogada avaliada em questão, de acordo com o
 *          algoritmo alphaBeta e o minMax, dado a profundidade maxDepth
 */
int MTDfRun(HexBoard *board, color player, int maxDepth, int *bestMove);

#endif
