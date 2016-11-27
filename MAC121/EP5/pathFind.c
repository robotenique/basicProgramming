#include <limits.h>
#include <stdio.h>
#include "pathFind.h"
#include "error.h"
/* Protótipos de funções locais */
bool verifyColorsMask(HexBoard *board, int id, unsigned char c_mask);
int getMinDistance_Q(s_Int *Q, int *dist, int hexCount, HexBoard *board,
    unsigned char c_mask);


DjkStorage *dijkstra(HexBoard *board, int start, int final,
    unsigned char c_mask, int noneWeight, int blackWeight, int whiteWeight) {
    int hexCount, i, QNb, u, tmpDist, *dist, *previous, *n_Nodes, *v;
    s_Int *Q;
    DjkStorage *djkS;

    if(!isHexagonValid(start, board))
        exit(EXIT_FAILURE);


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

    return djkS;
}

DjkPath *djkGetPath(DjkStorage *storage, int final) {
    int u, i;
    DjkPath *path;
    /* Verificação de erros */
    if(final >= 0 && storage->final >= 0 && final != storage->final)
        return NULL;

    if(!isHexagonValid(final, storage->board) &&
       !isHexagonValid(storage->final, storage->board))
        return NULL;

    /* Extrai as informações do storage */
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
/*
 * Function: getMinDistance_Q
 * --------------------------------------------------------
 * Retorna o hexágono do vetor 'Q' que possui a menor distância e que
 * satisfaz a bitmask de cores (c_mask)
 *
 * @args    Q: O vetor Q com os Nodes
 *          dist: O vetor com as distâncias dos nodes Q
 *          hexCount: A quantidade de hexágonos
 *          board: O tabuleiro com os hexágonos
 *          c_mask: Uma bitmask com as cores
 *
 * @return O número do hexágono que tem a menor distância
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
/*
* Function: verifyColorsMask
* --------------------------------------------------------
* Verifica se um hexágono de número = id satisfaz a máscara de cores.
* A bitmask de cores funciona assim:
* O dígito menos significativo é para o 'NONE'
* O dígito do meio é para a cor 'WHITE'
* O diǵito menos significativo é para a cor 'BLACK'
* Exemplo, c_mask = 0b011: Permite WHITE e NONE, mas não BLACK.
*
* @args    board: O tabuleiro com os hexágonos
*          id: O número do hexágono
*         c_mask: A bitmask das cores
*
* @return true se o hexágono satisfaz a máscara, false caso contrário
*/
bool verifyColorsMask(HexBoard *board, int id, unsigned char c_mask) {
    if(     ((c_mask & 0x01) && getHexagonColor(id, board) == NONE)
        ||  ((c_mask & 0x02) && getHexagonColor(id, board) == WHITE)
        ||  ((c_mask & 0x04) && getHexagonColor(id, board) == BLACK))
        return true;
    else
        return false;
}
