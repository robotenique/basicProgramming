#include <limits.h>
#include <stdio.h>
#include "pathFind.h"
#include "error.h"

/* Protótipos de funções locais */
bool verifyColorsMask(HexBoard *board, int id, unsigned char c_mask);
int getMinDistance_Q(s_Int *Q, int *dist, int hexCount, HexBoard *board,
    unsigned char c_mask);


void printPath(DjkPath *p) {
    int size, i;
    char *extra;
    fprintf(stderr,"CHAMANDO PRINTPATH\n");
    fflush(stderr);
    size = getHexagonsCount(p->board);
    extra = emalloc(sizeof(char)*size);
    for(i = 0; i < size; i++)
        extra[i] = 0;

    for(i = 0; i < p->n_Nodes; i++)
        extra[p->path[i]] = '*';

    extra[p->start] = 'S';
    extra[p->final] = 'D';
    bPrint2(p->board, extra);
}
/* Calcula o menor caminho para um Node, ou para todos os Nodes no HexBoard,
 * usando apenas hexágonos que combinam com a c_mask!
 * args: start: O hexágono inicial
 *       final: Hexágono final, ou uma posição inválida (id < 0) para
 *              calcular o caminho de todos os Nodes.
 *       c_mask: (color)Bitmask das cores para saber em quais Nodes é o
 *              algoritmo pode percorrer (ver verifyColorsMask).
 */
 /* Impl https://pt.wikipedia.org/wiki/Algoritmo_de_Dijkstra */

DjkStorage *dijkstra(HexBoard *board, int start, int final,
    unsigned char c_mask, int noneWeight, int blackWeight, int whiteWeight) {
    int hexCount, i, QNb, u, tmpDist, *dist, *previous, *n_Nodes, *v;
    s_Int *Q;
    DjkStorage *djkS;

    if(!isHexagonValid(start, board)) {
        printf("[Dijkstra] Posição inválida do Hexágono! D:\n");
        /* TODO: finish the function here?? */
    }

    hexCount = getHexagonsCount(board);
    dist = emalloc(sizeof(int)*hexCount);
    previous = emalloc(sizeof(int)*hexCount);
    n_Nodes = emalloc(sizeof(int)*hexCount);
    Q = emalloc(sizeof(int)*hexCount);
    QNb = 0;

    for(i = 0; i < hexCount; i++) {
        /* Todas as distâncias recebem peso "Infinito" */
        dist[i] = INT_MAX;
        /* Inicializa os outros arrays com valor indefinido */
        previous[i] = -1;
        n_Nodes[i] = -1;
        /* Se combina com c_mask ou pertence à borda, adiciona em Q */
        if(verifyColorsMask(board, i, c_mask)) {
            Q[i] = 1;
            QNb++;
        }
        else
            Q[i] = 0;
    }
    /* Distância do start vale 0 */
    dist[start] = 0;
    n_Nodes[start] = 0;

    /* Loop principal do Dijkstra */
    while(QNb > 0) {
        /* Pega o Node em Q com a menor distância que combina com c_mask */
        u = getMinDistance_Q(Q, dist, hexCount, board, c_mask);

        /* Retira o Node 'u' do array Q */
        Q[u] = 0;
        QNb--;

        /* Se 'u' é o Node final, o loop acaba */
        if(u == final)
            break;
        /* Se a menor distância é 'Infinito', quer dizer que todos os outros
         * Nodes não podem ser alcançados pelo algoritmo */
        if(dist[u] == INT_MAX)
            break;

        /* Vizinhos do node 'u' */
        v = getHexagonNeighbors(u, board);

        for(i = 0; i < getHexagonNeighborC(u, board); i++) {
            /* Verifica se o vizinho em questão existe */
            if(v[i] < 0)
                continue;
            /* O v[i] deve estar em Q, caso contrário ele já foi explorado
             * ou não combinou com c_mask
             */
            if(Q[v[i]] == 0)
                continue;

            if(!verifyColorsMask(board, v[i], c_mask))
                continue;

            /* Calcula a distância do 'start' até v[i].
             * obs: a distância no  HexBoard de a -> b == 1
             */
            tmpDist = 0;
            if(getHexagonColor(v[i], board) == WHITE)
                tmpDist = dist[u] + whiteWeight;
            else if(getHexagonColor(v[i], board) == BLACK)
                tmpDist = dist[u] + blackWeight;
            else
                tmpDist = dist[u] + noneWeight;

            /* Se o novo caminho é mais curto que o anterior,
             * troca os valores para o caminho calculado */
            if(tmpDist < dist[v[i]]) {
                dist[v[i]] = tmpDist;
                previous[v[i]] = u;
                Q[v[i]] = 1;
                n_Nodes[v[i]] = n_Nodes[u] + 1;
            }
        }

        free(v);
    }

    free(Q);

    /* Cria um DjkStorage com as informações */
    djkS = emalloc(sizeof(DjkStorage));
    djkS->board = board;
    djkS->start = start;
    djkS->final = final;
    djkS->colorMask = c_mask;
    djkS->dist = dist;
    djkS->previous = previous;
    djkS->n_Nodes = n_Nodes;

    /* imprimir dijkstra: dijkstraPrint(djkS); */
    return djkS;
}

/* Retorna o caminho (legível) para o node 'final'. */
DjkPath *djkGetPath(DjkStorage *storage, int final) {
    int u, i;
    DjkPath *path;
    /* Verificação de erros */
    if(final >= 0 && storage->final >= 0 && final != storage->final)
        return NULL;

    if(!isHexagonValid(final, storage->board) &&
       !isHexagonValid(storage->final, storage->board))
        return NULL;

    path = emalloc(sizeof(DjkPath));
    path->start = storage->start;
    if(final >= 0)
        path->final = final;
    else
        path->final = storage->final;
    path->length = storage->dist[path->final];
    path->n_Nodes = storage->n_Nodes[path->final];
    path->board = storage->board;

    if(path->length != INT_MAX && path->length != -1) {
        /* O caminho é construído */
        path->path = emalloc(sizeof(int)*(path->n_Nodes));
        u = path->final;
        i = path->n_Nodes - 1;
        while(storage->previous[u] != -1) {
            path->path[i] = u;
            u = storage->previous[u];
            i--;
        }
    }
    else {
        path->length = -1;
    }

    return path;
}

void djkDestroyPath(DjkPath *path) {
    if(path->length >= 0)
        free(path->path);
    free(path);
}

void djkDestroy(DjkStorage *djkS) {
    free(djkS->previous);
    free(djkS->dist);
    free(djkS->n_Nodes);
    free(djkS);
}

/* Retorna o Node em 'Q' que possui a menor distância e combina com a c_mask,
 * além de considerar caso seja uma borda.
 */
/*
 * Q = Um conjunto de Nodes , possui Nodes na c_mask
 * dist = Array com a distância dos Nodes
 * hexCount = Número de hexágonos em Q e em dist
 * board = O tabuleiro hexagonal para procurar as cores
 * c_mask = Bitmask com as cores aceitas
 */
int getMinDistance_Q(s_Int *Q, int *dist, int hexCount, HexBoard *board,
    unsigned char c_mask) {
    int i, min;
    i = min = 0;
    /* Procura o primeiro Node em Q que combina com c_mask */
    for(; i < hexCount; i++)
        if(Q[i]==1 && verifyColorsMask(board, i, c_mask)) {
            min = i;
            break;
        }

    /* Procura em Q o Node com a menor distância */
    for(; i < hexCount; i++)
        if(Q[i]==1 && dist[i] < dist[min])
            min = i;

    return min;
}

/* Check if a hexagon in the board match the colorMask.
 * Returns true if the c_mask is matched or the Hexagon is from the border.
 *         false if not.
 */
/* about the c_mask:
 * It's a bitmask. It uses the 3 bits;
 * The last significant bit is for the 'NONE' color.
 * The second bit is for the 'WHITE' color;
 * The most significant bit is for the 'BLACK' color;
 * For example: 1)the c_mask = 0b111 : the function returns true if the hexagon
 *              is NONE or WHITE or BLACK.
 *              2)the c_mask = 0b101 : the function returs true if the hexagon
 *              is BLACK or NONE.
 */
bool verifyColorsMask(HexBoard *board, int id, unsigned char c_mask) {
    if(     ((c_mask & 0x01) && getHexagonColor(id, board) == NONE)
        ||  ((c_mask & 0x02) && getHexagonColor(id, board) == WHITE)
        ||  ((c_mask & 0x04) && getHexagonColor(id, board) == BLACK))
        return true;
    else
        return false;
}
