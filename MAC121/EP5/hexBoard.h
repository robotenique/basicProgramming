/*
 * @author: Juliano Garcia de Oliveira
 * nº usp = 9277086
 * MAC0121
 * 28/11/2016
 * Header da HexBoard, que é uma estrutura de dados que representa um tabuleiro
 * composto de hexágonos (struct Hexagon); Muita coisa implementada não seria
 * possível sem a ajuda do guia da redblobgames, disponível em
 * http://www.redblobgames.com/grids/hexagons/
 */
#ifndef _HEX_BOARD_H_
#define _HEX_BOARD_H_
#include "hexTypes.h"

/* Definições dos tipos */
typedef struct {
    s_Int color; /* pode ser NONE, WHITE ou BLACK */
} Hexagon;

typedef struct {
    s_Int size; /* O tamanho da grid. No EP, size = 14 */
    unsigned int turnN; /* Número do turno atual */
    color player; /* O jogador que deve jogar */
    Hexagon *hexs; /* A matriz de hexágonos */
} HexBoard;

/*
 * Function: newHexBoard
 * --------------------------------------------------------
 * Cria uma nova HexBoard e inicializa seus valores.
 *
 * @args    size: O tamanho da grid. O total de hexágonos será size^2
 *
 * @return Retorna um ponteiro para uma HexBoard, com tamanho size.
 */
HexBoard *newHexBoard(s_Int size);
/*
 * Function: cloneHexBoard
 * --------------------------------------------------------
 * Retorna uma nova HexBoard que é uma cópia da HexBoard fornecida.
 *
 * @args    board: O tabuleiro de hexágonos
 *
 * @return Uma cópia da board. Deve ser destruído usando destroyHexBoard.
 */
HexBoard *cloneHexBoard(HexBoard *board);
/*
 * Function: destroyHexBoard
 * --------------------------------------------------------
 * Libera a memória de uma HexBoard
 *
 * @args    board: O tabuleiro de hexágonos
 *
 * @return
 */
void destroyHexBoard(HexBoard *board);
/*
 * Function: stringfyBoard
 * --------------------------------------------------------
 * Transforma o tabuleiro em uma "mask", isto é, transforma o tabuleiro em uma
 * string que o representa. Cada string é única e representa uma configuração
 * específica do tabuleiro.
 *
 * @args    board: O tabuleiro de hexágonos
 *
 * @return  Uma string representando o tabuleiro
 */
char *stringfyBoard(HexBoard *board);


/* Funções dos hexágonos */
/*
 * Function: getHexagonsCount
 * --------------------------------------------------------
 * Calcula a quantidade de hexágonos no tabuleiro
 *
 * @args    board: O tabuleiro de hexágonos
 *
 * @return  A quantidade de hexágonos no tabuleiro (incluindo as bordas)
 */
int getHexagonsCount(HexBoard *board);
/*
 * Function: setHexagonColor
 * --------------------------------------------------------
 * Altera a cor de um hexágono com o 'id' especificado.
 *
 * @args    id: O número do hexágono
 *          board: O tabuleiro de hexágonos
 *          color: A cor para alterar o hexágono especificado
 *
 * @return
 */
void setHexagonColor(int id, HexBoard *board, color color);
/*
 * Function: getHexagonColor
 * --------------------------------------------------------
 * Calcula a cor de um dado hexágono especificado
 *
 * @args     id: O número do hexágono
 *           board: O tabuleiro de hexágonos
 *
 * @return  A cor do hexágono (BLACK, WHITE ou NONE). Se é um hexágono
 *          inválido, retorna INVALID.
 */
color getHexagonColor(int id, HexBoard *board);
/*
 * Function: isHexagonValid
 * --------------------------------------------------------
 * Verifica se um ID do hexágono é válido, isto é, está dentro do tabuleiro.
 *
 * @args     id: O número do hexágono
 *           board: O tabuleiro de hexágonos
 *
 * @return true se é válido, false caso contrário
 */
bool isHexagonValid(int id, HexBoard *board);
/*
 * Function: isHexagonPlayable
 * --------------------------------------------------------
 * Verifica se um dado hexágono é jogável, isto é, se é válido e se não
 * há nenhuma cor atual nele (cor = NONE)
 *
 * @args     id: O número do hexágono
 *           board: O tabuleiro de hexágonos
 *
 * @return -1 se o hexágono é inválido, 1 se é válido e não está ocupado,
 *         0 caso contrário
 */
int isHexagonPlayable(int id, HexBoard *board);
/*
 * Function: getHexagonNeighborC
 * --------------------------------------------------------
 * Calcula o número de vizinhos de um hexágono. Se o hexágono é inválido,
 * retorna -1, se é um hexágono comum retorna 6. Se é um hexágono da borda,
 * retorna o tamanho do tabuleiro.
 *
 * @args     id: O número do hexágono
 *           board: O tabuleiro de hexágonos
 *
 * @return A quantidade de vizinhos de um hexágono de número = id
 */
int getHexagonNeighborC(int id, HexBoard *board);
/*
 * Function: getHexagonNeighbors
 * --------------------------------------------------------
 * Calcula a posição dos vizinhos de um hexágono de número = id
 * Ordem dos vizinhos:
 *
 *                 _____
 *                /     \
 *          _____/   3   \_____
 *         /     \       /     \
 *        /   5   \_____/   1   \
 *        \       /     \       /
 *         \_____/  ID   \_____/
 *         /     \       /     \
 *        /   6   \_____/   2   \
 *        \       /     \       /
 *         \_____/   4   \_____/
 *               \       /
 *                \_____/
 *
 * @args     id: O número do hexágono
 *           board: O tabuleiro de hexágonos
 *
 * @return Um array com os números dos vizinhos do hexágono de número = id. Se
 *         o hexágono é inválido, retorna NULL.
 */
int *getHexagonNeighbors(int id, HexBoard *board);

/* Funções para verificar bordas */
/*
 * Function: isHexNearTopBorder
 * --------------------------------------------------------
 * Verifica se um hexágono está na borda superior do tabuleiro
 *
 * @args     id: O número do hexágono
 *           board: O tabuleiro de hexágonos
 *
 * @return  1 se está na borda superior, 0 caso contrário. O caso -1 só é
 *          usado para debug.
 */
bool isHexNearTopBorder(int id, HexBoard *board);
/*
 * Function: isHexNearBotBorder
 * --------------------------------------------------------
 * Verifica se um hexágono está na borda inferior do tabuleiro
 *
 * @args     id: O número do hexágono
 *           board: O tabuleiro de hexágonos
 *
 * @return  1 se está na borda inferior, 0 caso contrário. O caso -1 só é
 *          usado para debug.
 */
bool isHexNearBotBorder(int id, HexBoard *board);
/*
 * Function: isHexNearLeftBorder
 * --------------------------------------------------------
 * Verifica se um hexágono está na borda esquerda do tabuleiro
 *
 * @args     id: O número do hexágono
 *           board: O tabuleiro de hexágonos
 *
 * @return  1 se está na borda esquerda, 0 caso contrário. O caso -1 só é
 *          usado para debug.
 */
bool isHexNearLeftBorder(int id, HexBoard *board);
/*
 * Function: isHexNearRightBorder
 * --------------------------------------------------------
 * Verifica se um hexágono está na borda direita do tabuleiro
 *
 * @args     id: O número do hexágono
 *           board: O tabuleiro de hexágonos
 *
 * @return  1 se está na borda direita, 0 caso contrário. O caso -1 só é
 *          usado para debug.
 */
bool isHexNearRightBorder(int id, HexBoard *board);
/*
 * Function: boardGetTopBorder
 * --------------------------------------------------------
 * Retorna a borda superior do tabuleiro.
 *
 * @args     board: O tabuleiro de hexagonos
 *
 * @return O número do hexágono que é a borda superior do tabuleiro.
 */
bool isHexTopBorder(int id, HexBoard *board);
/*
 * Function: boardGetBotBorder
 * --------------------------------------------------------
 * Retorna a borda inferior do tabuleiro.
 *
 * @args    board: O tabuleiro de hexagonos
 *
 * @return O número do hexágono que é a borda inferior do tabuleiro.
 */
bool isHexBotBorder(int id, HexBoard *board);
/*
 * Function: boardGetLeftBorder
 * --------------------------------------------------------
 * Retorna a borda esquerda do tabuleiro.
 *
 * @args    board: O tabuleiro de hexagonos
 *
 * @return O número do hexágono que é a borda esquerda do tabuleiro.
 */
bool isHexLeftBorder(int id, HexBoard *board);
/*
* Function: boardGetRightBorder
* --------------------------------------------------------
* Retorna a borda direita do tabuleiro.
*
* @args    board: O tabuleiro de hexagonos
*
* @return O número do hexágono que é a borda direita do tabuleiro.
*/
bool isHexRightBorder(int id, HexBoard *board);

/* Função para retornar o vizinho de um hexágono individualmente */
/*
 * Function: getHexTopLeftN
 * --------------------------------------------------------
 * Retorna o vizinho superior esquerdo de um hexágono de número = id do
 * tabuleiro.
 *
 * @args    id: O número do hexágono
 *           board: O tabuleiro de hexágonos
 *
 * @return  Um inteiro que representa o número do hexágono que é vizinho
 *          superior esquerdo do hexágono de número = id.
 */
int getHexTopLeftN(int id, HexBoard *board);
/*
 * Function: getHexTopRightN
 * --------------------------------------------------------
 * Retorna o vizinho superior direito de um hexágono de número = id do
 * tabuleiro.
 *
 * @args    id: O número do hexágono
 *           board: O tabuleiro de hexágonos
 *
 * @return  Um inteiro que representa o número do hexágono que é vizinho
 *          superior direito do hexágono de número = id.
 */
int getHexTopRightN(int id, HexBoard *board);
/*
 * Function:getHexLeftN
 * --------------------------------------------------------
 * Retorna o vizinho esquerdo de um hexágono de número = id do tabuleiro.
 *
 * @args    id: O número do hexágono
 *           board: O tabuleiro de hexágonos
 *
 * @return  Um inteiro que representa o número do hexágono que é vizinho
 *          esquerdo do hexágono de número = id.
 */
int getHexLeftN(int id, HexBoard *board);
/*
 * Function:getHexRightN
 * --------------------------------------------------------
 * Retorna o vizinho direito de um hexágono de número = id do tabuleiro.
 *
 * @args    id: O número do hexágono
 *           board: O tabuleiro de hexágonos
 *
 * @return  Um inteiro que representa o número do hexágono que é vizinho
 *          direito do hexágono de número = id.
 */
int getHexRightN(int id, HexBoard *board);
/*
 * Function: getHexBotLeftN
 * --------------------------------------------------------
 * Retorna o vizinho inferior esquerdo de um hexágono de número = id do
 * tabuleiro.
 *
 * @args    id: O número do hexágono
 *           board: O tabuleiro de hexágonos
 *
 * @return  Um inteiro que representa o número do hexágono que é vizinho
 *          inferior esquerdo do hexágono de número = id.
 */
int getHexBotLeftN(int id, HexBoard *board);
/*
 * Function: getHexBotRightN
 * --------------------------------------------------------
 * Retorna o vizinho inferior direito de um hexágono de número = id do
 * tabuleiro.
 *
 * @args    id: O número do hexágono
 *           board: O tabuleiro de hexágonos
 *
 * @return  Um inteiro que representa o número do hexágono que é vizinho
 *          inferior direito do hexágono de número = id.
 */
int getHexBotRightN(int id, HexBoard *board);


/* Funções para obter as bordas */
/*
 * Function: boardGetTopBorder
 * --------------------------------------------------------
 * Retorna a borda superior do tabuleiro de hexágonos.
 *
 * @args    board: O tabuleiro de hexágonos
 *
 * @return O hexágono que é a borda superior do tabuleiro 'board'
 */
int boardGetTopBorder(HexBoard *board);
/*
 * Function: boardGetBotBorder
 * --------------------------------------------------------
 * Retorna a borda inferior do tabuleiro de hexágonos.
 *
 * @args    board: O tabuleiro de hexágonos
 *
 * @return O hexágono que é a borda inferior do tabuleiro 'board'
 */
int boardGetBotBorder(HexBoard *board);
/*
 * Function: boardGetLeftBorder
 * --------------------------------------------------------
 * Retorna a borda esquerda do tabuleiro de hexágonos.
 *
 * @args    board: O tabuleiro de hexágonos
 *
 * @return O hexágono que é a borda esquerda do tabuleiro 'board'
 */
int boardGetLeftBorder(HexBoard *board);
/*
 * Function: boardGetRightBorder
 * --------------------------------------------------------
 * Retorna a borda direita do tabuleiro de hexágonos.
 *
 * @args    board: O tabuleiro de hexágonos
 *
 * @return O hexágono que é a borda direita do tabuleiro 'board'
 */
int boardGetRightBorder(HexBoard *board);

/* Função auxiliar */
/*
 * Function: boardPrint
 * --------------------------------------------------------
 * Imprime o tabuleiro, caso a flag debug == true. A função transforma
 * o tabuleiro em uma matriz, e o imprime normalmente.
 *
 * @args    board: O tabuleiro que será impresso
 *
 * @return
 */
void boardPrint(HexBoard *board);
#endif
