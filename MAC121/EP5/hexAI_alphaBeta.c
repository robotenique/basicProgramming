/*
 * @author: Juliano Garcia de Oliveira
 * nº usp = 9277086
 * MAC0121
 * 28/11/2016
 * Implementação do algoritmo de redução de gameTree alpha beta.
 */
#include <limits.h>
#include <string.h>
#include <stdio.h>
#include "hexAI_alphaBeta.h"
#include "pathFind.h"
#include "hashTable.h"
#include "game.h"
#include "error.h"

/* Tipos usados na transposition Table */
#define LOWERBOUND 1
#define UPPERBOUND 2
#define EXACT 0


/* Protótipos de Funções locais */
int max(int x, int y, int * xLower);
int min(int x, int y, int * xHigher);
int abGetVal(HexBoard *board, color player, int depth);
transTEntry * getCache(HexBoard *board, HashTable *transTable);
void abCache(HexBoard *board, HashTable *transTable, int type, int score, int depth);
HexBoard * abNewChild(HexBoard *board, int i);


/* Variáveis usadas para controle de tempo */
float timeLen;
clock_t tSpent;


int alphaBetaAlgorithm(HexBoard * board, int alpha, int beta, int depth,
    int maxDepth, color player, char type, HashTable *transTable,
    int *bestM) {
    int i, b, a, auxVal;
    /* value = O score / peso associado
     * nHexs = O número de hexágonos no tabuleiro
     */
    int mod, value, nHexs;
    transTEntry *cache;
    HexBoard *child;

    i = mod = value = nHexs = getHexagonsCount(board) - 4;

    /* Checando a maxDepth */
    if(maxDepth < 1) exit(EXIT_FAILURE);

    /* Verifica se o tabuleiro atual já foi calculado antes */
    cache = getCache(board, transTable);
    if(cache != NULL && cache->depth >= depth) {
        switch (cache->type) {
            case LOWERBOUND:
                if(cache->score >= beta)
                    return cache->score;
                alpha = max(alpha, cache->score, NULL);
                break;
            case UPPERBOUND:
                if(cache->score <= alpha)
                    return cache->score;
                beta = min(beta, cache->score, NULL);
                break;
            case EXACT:
                if(cache->score >= beta)
                    return cache->score;
                if(cache->score >= alpha)
                    return cache->score;
                alpha = max(alpha, cache->score, NULL);
                beta = min(beta, cache->score, NULL);
                break;
        }
    }

    /* O tabuleiro é uma folha, então é avaliado */
    if(depth == maxDepth || checkVictory(board) != NONE) {
        if(player == WHITE)
            return abGetVal(board, WHITE, depth);
        else
            return abGetVal(board, BLACK, depth);
    }

    /* Minimiza o beta */
    if(type == MIN) {
        value = +INT_MAX;
        tSpent = clock() - t;
        timeLen = ((double)tSpent)/CLOCKS_PER_SEC;
        if((timeLen/10) > 0.285)
            return value;
        i = 0;
        b = beta; /* Salva o valor original de beta */
        /* Para cada elemento da árvore, até o prunning */
        while(i <= nHexs && value > alpha) {
            if(!isHexagonPlayable(i, board)) {
                i++;
                continue;
            }
            child = abNewChild(board, i);
            auxVal = alphaBetaAlgorithm(child, alpha, b, depth + 1,
                    maxDepth, player, MAX, transTable, bestM);
            value = min(value, auxVal, &mod);
            /* Tenta diminuir o beta */
            b = min(b, value, NULL);
            destroyHexBoard(child);
            i++;
        }
    }
    else { /* Maximiza o alpha */
        value = -INT_MAX;
        tSpent = clock() - t;
        timeLen = ((double)tSpent)/CLOCKS_PER_SEC;
        if((timeLen/10) > 0.285)
            return value;
        i = 0;
        a = alpha; /* Salva o valor original de alpha */
        while(i <= nHexs && value < beta) {
            if(!isHexagonPlayable(i, board)) {
                i++;
                continue;
            }
            child = abNewChild(board, i);
            auxVal = alphaBetaAlgorithm(child, a, beta, depth + 1,
                    maxDepth, player, MIN, transTable, bestM);
            value = max(value, auxVal, &mod);
            /* Foi encontrada uma jogada melhor */
            if(mod == 1)
                *bestM = i;
            a = max(a, value, NULL);
            destroyHexBoard(child);
            i++;
        }
    }

    /* Prunning do alpha */
    if (value <= alpha) {
        /* folhas com 'value' baixo significa uma UPPERBOUND */
        abCache(board, transTable, UPPERBOUND, value, depth);
    }
    /* Foi encontrado um resultado preciso */
    if(value > alpha && value < beta) {
        abCache(board, transTable, EXACT, value, depth);
    }
    /* Prunning do beta */
    if(value >= beta) {
        /* folhas com 'value' alto significa uma LOWERBOUND */
        abCache(board, transTable, LOWERBOUND, value, depth);
    }

    return value;
}

int abKeyCmp(const void *a, const void *b) {
    return strcmp((char*)a, (char*)b);
}
/*
 * Function: getCache
 * --------------------------------------------------------
 * Consulta a transTable para obter uma entrada que contém informações do
 * tabuleiro especificado como parâmetro.
 *
 * @args    board: O tabuleiro para ser pesquisado
 *          transTable: a transposition table
 *
 * @return Uma entrada da transposition table que contém as informações sobre
 *         determinado tabuleiro, ou NULL quando o tabuleiro não está na
 *         transposition table.
 */
transTEntry *getCache(HexBoard *board, HashTable *transTable) {
    char *str;
    transTEntry *entry;

    if(transTable == NULL) return NULL;
    str = stringfyBoard(board);
    entry = HashTableGet(transTable, str);
    free(str);
    return entry;
}
/*
 * Function: abCache
 * --------------------------------------------------------
 * Adiciona na transposition table as informações de um tabuleiro atual.
 *
 * @args    board: O tabuleiro do jogo
 *          transTable: A HashTable que representa a transposition table
 *          type: O tipo daquele tabuleiro (MIN? MAX?)
 *          score: O valor dado ao tabuleiro
 *          depth: A profundidade que ele foi calculado no algoritmo alphaBeta
 *
 *
 * @return
 */
void abCache(HexBoard *board, HashTable *transTable, int type, int score,int depth) {
    char *str;
    transTEntry *entry;

    if(transTable == NULL) return;
    str = stringfyBoard(board);

    entry = emalloc(sizeof(transTEntry));
    entry->depth = depth;
    entry->score = score;
    entry->type = type;
    HashTablePut(transTable, str, entry);
}
/*
 * Function: abGetVal
 * --------------------------------------------------------
 * Avalia um dado tabuleiro (que é uma folha da árvore de alpha Beta), e
 * retorna o valor / peso / pontuação daquele dado tabuleiro. Essa função
 * inicialmente verifica se houve vitória, atribuindo um peso maior ao
 * tabuleiro. Senão, faz um dijkstra até o hexágono onde o jogador venceria.
 * Com base no tamanho do caminho calculado pelo dijkstra, ele dá um valor
 * para a jogada.
 *
 * @args    board: O tabuleiro do jogo
 *          player: A cor do jogador (WHITE ou BLACK)
 *          depth: A profundidade da árvore
 *
 * @return O valor do tabuleiro
 */
int abGetVal(HexBoard *board, color player, int depth) {
    int start, end, value;
    char mask;
    color winner;
    DjkStorage *djkS;
    DjkPath *djkPath;

    /* Inicialmente, verifica a vitória */
    winner = checkVictory(board);
    if(winner != player && winner != NONE)
        return 500;
    if(winner == player)
        return 3000;


    if(player == BLACK) {
        start = boardGetBotBorder(board);
        end = boardGetTopBorder(board);
        mask = 0x04 + 0x01; /* Pretas e vazias */
    }
    else {
        start = boardGetLeftBorder(board);
        end = boardGetRightBorder(board);
        mask = 0x02 + 0x01; /* Brancas e vazias */
    }

    /* Calcula a distância necessária para a vitória,
     * incluindo os hexágonos não colocados (NONE) com um peso diferente... */
    djkS = dijkstra(board, start, end, mask, 15, 0, 0);
    djkPath = djkGetPath(djkS, -1);
    if(djkPath->length < 0) {
        djkDestroyPath(djkPath);
        djkDestroy(djkS);
        return 0;
    }

    /* Calcula o valor/peso */
    value = 300 - djkPath->length;

    djkDestroyPath(djkPath);
    djkDestroy(djkS);

    return value;
}
/*
 * Function: abNewChild
 * --------------------------------------------------------
 * Adiciona um novo Node na árvore alphaBeta, ou seja, uma nova jogada é feita,
 * e esse tabuleiro é retornado.
 *
 * @args    board : O tabuleiro do jogo
 *          i: o ID do hexágono para mudar a cor
 *
 * @return O tabuleiro com a jogada executada
 */
HexBoard * abNewChild(HexBoard *board, int i) {
    HexBoard *child;

    child = cloneHexBoard(board);
    child->hexs[i].color = child->player;
    child->turnN++;
    if(board->player == WHITE)
        child->player = BLACK;
    else
        child->player = WHITE;

    return child;
}
/*
 * Function: max
 * --------------------------------------------------------
 * Retorna o máximo entre dois números, e se o primeiro é maior que o segundo.
 *
 * @args    x: Um número
 *          y: Um número
 *          xLower: Um ponteiro para um inteiro que será o indicador
 *
 * @return O máximo entre x e y, e *xLower indica qual deles foi o menor.
 */
int max(int x, int y, int * xLower) {
    if(x < y) {
        if(xLower != 0) *xLower = 1;
        return y;
    } else {
        if(xLower != 0) *xLower = 0;
        return x;
    }
}
/*
 * Function: min
 * --------------------------------------------------------
 * Retorna o mínimo entre dois números, e se o primeiro é maior que o segundo.
 *
 * @args    x: Um número
 *          y: Um número
 *          xHigher: Um ponteiro para um inteiro que será o indicador
 *
 * @return O mínimo entre x e y, e *xHigher indica qual deles foi o maior.
 */
int min(int x, int y, int * xHigher) {
    if(x < y) {
        if(xHigher != 0) *xHigher = 0;
        return x;
    } else {
        if(xHigher != 0) *xHigher = 1;
        return y;
    }
}
