/*
* @author: Juliano Garcia de Oliveira
* nº usp = 9277086
* MAC0121
* 28/11/2016
* Header da implementação do algoritmo dijkstra para calcular caminhos
* no tabuleiro.
* Foi usado notações de: https://en.wikipedia.org/wiki/Dijkstra's_algorithm
*/
#ifndef _PATH_FIND_H_
#define _PATH_FIND_H_
#include "hexBoard.h"
#include "hexTypes.h"

/* Armazena informações após executar o dijkstra */
typedef struct {
    HexBoard *board; /* O tabuleiro original */
    int start; /* O número do hexágono inicial */
    /* O número do hexágono final ou -1 quando é um dijkstra completo */
    int final;
    /* Bitmask das cores permitidas (NONE | WHITE | BLACK)*/
    s_Int colorMask;
    /* Vetor com as menores distâncias dos hexágonos até o hexágono final */
    int * dist;
    /* Define o menor caminho dos hexágonos até o hexágono final */
    int * previous;
    /* Armazena a quantidade de hexágonos até o hexágono final */
    int * n_Nodes;
} DjkStorage;

/* Armazena informações do caminho calculado */
typedef struct {
    HexBoard *board; /* O tabuleiro original */
    int start; /* O número do hexágono inicial */
    int final; /* O número do hexágono final */
    int length;  /* O número do vértices no caminho */
    int n_Nodes; /* Número de hexágonos no caminho */
    /* Vetor com o caminho calculado (número dos hexágonos).
     * O hexágono inicial não está incluído neste vetor */
    int * path;
} DjkPath;
/*
 * Function: dijkstra
 * --------------------------------------------------------
 * Calcula o menor caminho até um 'node' final, ou para todos os nodes no
 * tabuleiro (dijkstra completo), porém só com os hexágonos que satisfazem
 * a bitmask recebida como argumento (c_mask). A implementação desse dijkstra
 * usou notações (nomes de variáveis, etc) como explicado nesta página:
 * https://pt.wikipedia.org/wiki/Algoritmo_de_Dijkstra
 *
 * @args    board: O tabuleiro de hexágonos
 *          start: O hexágono inicial
 *          final: O hexágono final ou (-1) para calcular um dijkstra completo
 *          c_mask: A bitmask das cores para saber em quais hexágonos o
 *                  algoritmo deve percorrer.
 *          noneWeight: O peso dos hexágonos sem cores
 *          blackWeight: O peso dos hexágonos de cor BLACK
 *          whiteWeight: O peso dos hexágonos de cor WHITE
 *
 * @return Uma instância do tipo DjkStorage com as informações do dijkstra
 */
DjkStorage *dijkstra(HexBoard *board, int start, int final,
    unsigned char c_mask, int noneWeight, int blackWeight, int whiteWeight);
/*
 * Function: djkGetPath
 * --------------------------------------------------------
 * Transforma o DjkStorage recebido em um DjkPath com o caminho já
 * calculado.
 *
 * @args    storage : o DjkStorage com as informações do dijkstra
 *          final: O node final (pode ser -1 para um dijkstra completo).
 *
 * @return um DjkPath com as informações do dijkstra
 */
DjkPath * djkGetPath(DjkStorage *storage, int final);
/*
 * Function: djkDestroyPath
 * --------------------------------------------------------
 * Destrói um objeto DjkPath, liberando sua memória
 *
 * @args   path : Um DjkPath
 *
 * @return
 */
void djkDestroyPath(DjkPath *path);
/*
 * Function: djkDestroy
 * --------------------------------------------------------
 * Destrói um DjkStorage, liberando a memória ocupada
 *
 * @args    djkS: Um DjkStorage
 *
 * @return
 */
void djkDestroy(DjkStorage *djkS);
#endif
