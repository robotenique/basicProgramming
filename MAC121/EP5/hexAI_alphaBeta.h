/*
 * @author: Juliano Garcia de Oliveira
 * nº usp = 9277086
 * MAC0121
 * 28/11/2016
 * Header do algoritmo de redução de gameTree alpha beta.
 */
#ifndef __HEX_AI_ALPHA_BETA_H__
#define __HEX_AI_ALPHA_BETA_H__
#include <time.h>
#include "hashTable.h"
#include "hexBoard.h"
#define MIN 0
#define MAX 1
/* Usado para estipular um limite de tempo */
clock_t t;

/* Uma entry da minha Transposition Table */
typedef struct {
	int score;
	int type;
	int depth;
} transTEntry;

/*
 * Function: alphaBetaAlgorithm
 * --------------------------------------------------------
 * Retorna o valor de um tabuleiro após passar pelo alphaBeta. Enquanto
 * não chegar em uma folha da árvore, chama a função recursivamente, criando
 * uma árvore implicitamente e percorrendo-a através de uma DFS.
 * O algoritmo de alphaBeta possui os parâmetros "alpha" e o "beta", que são
 * usados para minimizar / maximizar determinados ramos da árvore, e
 * determinar se é possível fazer o 'prunning' ou 'cutoff', que é interromper
 * a recursão = Na prática, corta um ramo de árvore, que não precisa ser
 * avaliado.
 * O algoritmo aqui implementado não usa só uma árvore, mas também salva na
 * Transposition table, para não ter que calcular novamente caso um tabuleiro
 * já tenha sido calculado ('memoization'). Isto é o 'cache' do algoritmo.
 * Para mais detalhes, consultar o relatório.
 *
 * @args    board: O tabuleiro do jogo em questão
 *          alpha:  O valor do alpha
 *          beta: o valor do beta
 *          depth: Profundidade atual da árvore
 *          maxDepth: A profundidade máxima da árvore que é permitida
 *          player: O cor do player em questão (WHITE ou BLACK)
 *          type: O tipo de análise que está fazendo (MAX, MIN, )
 *          transTable: A transposition Table, que contém tabuleiros já
 *                      calculados.
 *          bestM: Um ponteiro para o melhor movimento. Seu valor é atualizado
 *                 dentro dessa função.
 *
 * @return O valor com a melhor jogada escolhida.
 */
int alphaBetaAlgorithm(HexBoard * board, int alpha, int beta, int depth,
    int maxDepth, color player, char type, HashTable *transTable, int *bestM);
/*
 * Function: abKeyCmp
 * --------------------------------------------------------
 * Função de comparação entre duas chaves. É usado para comparar os valores
 * das chaves da transposition table (a hashTable).
 *
 * @args    a : Uma string
 *          b: Uma string
 *
 * @return 0 se são iguais, 1 se a > b, -1 caso contrário
 */
int abKeyCmp(const void *a, const void *b);

#endif
