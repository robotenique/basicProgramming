#include <limits.h>
#include <string.h>
#include "hexAI_alphaBeta.h"
#include "pathFind.h"
#include "hashTable.h"
#include "game.h"
#include "error.h"
/* Macros usados na transposition Table */
#define LOWERBOUND 1
#define UPPERBOUND 2
#define EXACT 0
/* Funções locais */
int max(int x, int y, int * xLower);
int min(int x, int y, int * xHigher);
int abGetVal(HexBoard *board, color player, int depth);
transTEntry * getCache(HexBoard *board, HashTable *transTable);
void abCache(HexBoard *board, HashTable *transTable, int type, int score, int depth);
HexBoard * abNewChild(HexBoard *board, int i);

int alphaBetaAlgorithm(HexBoard * board, int alpha, int beta, int depth,
    int maxDepth, color player, char type, HashTable *transTable,
    int *bestM) {
    int i, b, a, auxVal;
    /* mod = Ponteiro para verificar se houve modificação,
     * value = O score / peso associado
     * nHexs = O número de hexágonos no tabuleiro
     */
    int mod, value, nHexs;
    transTEntry *cache;
    HexBoard *child;

    i = mod = value = nHexs = getHexagonsCount(board) - 4;

    /* Checando a maxDepth */
    if(maxDepth < 1) exit(EXIT_FAILURE);

    cache = getCache(board, transTable);
    if(cache != NULL && cache->depth >= depth) {
        stats_cacheAccess++;
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

    if(type == MIN) {
        value = +INT_MAX;
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
    else {
        value = -INT_MAX;
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
        /* falhas com 'value' baixo significa uma UPPERBOUND */
        abCache(board, transTable, UPPERBOUND, value, depth);
    }
    /* Foi encontrado um resultado preciso */
    if(value > alpha && value < beta) {
        abCache(board, transTable, EXACT, value, depth);
    }
    /* Prunning do beta */
    if(value >= beta) {
        /* falhas com 'value' alto significa uma LOWERBOUND */
        abCache(board, transTable, LOWERBOUND, value, depth);
    }

    return value;
}

transTEntry *getCache(HexBoard *board, HashTable *transTable) {
    char *str;
    transTEntry *entry;
    if(transTable == NULL) return NULL;

    str = stringfyBoard(board);
    entry = HashTableGet(transTable, str);
    free(str);
    return entry;
}

void abCache(HexBoard *board, HashTable *transTable, int type, int score, int depth) {
    char *str;
    transTEntry *entry;

    if(transTable == NULL) return;
    stats_newCached++;
    str = stringfyBoard(board);

    entry = emalloc(sizeof(transTEntry));
    entry->depth = depth;
    entry->score = score;
    entry->type = type;

    HashTablePut(transTable, str, entry);

}

int abKeyCmp(const void *a, const void *b) {
    return strcmp((char*)a, (char*)b);
}

int abGetVal(HexBoard *board, color player, int depth) {
    int start, end, value;
    char mask;
    color winner;
    DjkStorage *djkS;
    DjkPath *djkPath;
    stats_evalLeaf++;

    /* Inicialmente, verifica a vitória */
    winner = checkVictory(board);
    if(winner != player && winner != NONE)
        return 500;
    if(winner == player)
        return 3000;

    /* A função faz dois Dijkstra:
     * Um da primeira borda até o último hexágono que foi colocado,
     * e outro do último hexágono colocado até a segunda borda.
     */
    if(player == WHITE) {
        start = boardGetBotBorder(board);
        end = boardGetTopBorder(board);
        mask = 0x01+0x02;
    }
    else {
        start = boardGetLeftBorder(board);
        end = boardGetRightBorder(board);
        mask = 0x04 + 0x01;
    }

    /* Calcula a distância necessária para a vitória,
     * incluindo os hexágonos não colocados (NONE) com um peso diferente... */
    djkS = dijkstra(board, start, end, mask, 15, 0, 0);
    djkPath = djkGetPath(djkS, -1);
    if(djkPath->length < 0) return 0;

    /* Calcula o valor/peso */
    value = 300 - djkPath->length;

    djkDestroyPath(djkPath);
    djkDestroy(djkS);

    return value;
}

HexBoard * abNewChild(HexBoard *board, int i) {
    HexBoard *child;
    stats_nodes++;
    child = cloneHexBoard(board);
    child->hexs[i].color = child->player;
    child->turnN++;
    if(board->player == WHITE)
        child->player = BLACK;
    else
        child->player = WHITE;

    return child;
}

int max(int x, int y, int * xLower) {
    if(x < y) {
        if(xLower != 0) *xLower = 1;
        return y;
    } else {
        if(xLower != 0) *xLower = 0;
        return x;
    }
}

int min(int x, int y, int * xHigher) {
    if(x < y) {
        if(xHigher != 0) *xHigher = 0;
        return x;
    } else {
        if(xHigher != 0) *xHigher = 1;
        return y;
    }
}
