#include <limits.h>
#include "pathFind.c"


/* Stores information after a dijkstra algorithm run */

typedef struct {
    HexBoard *board; /* The original hexagonal board */
    int start; /* The start node ID*/
    /* The final node ID or a invalid node ID if the traverse is 100% */
    int final;
    /* A color mask available to traverse (NONE | WHITE | BLACK)*/
    s_Int colorMask;
    /* Array of the shortest distances to all nodes or to the final node */
    int * dist;
    /* array to define the shortest path to all nodes or to the final node */
    int * previous;
    /* Array to store how many nodes in the path to the final node */
    int * n_Nodes;
} DjkStorage;

typedef struct {
    HexBoard *board; /* The original hexagonal board */
    int start; /* The start node ID*/
    int final; /* The final node ID*/
    int length;  /* Number of jumps in the path */
    int n_Nodes; /* Number of nodes in the path */
    /* Array (size = length) with the path.
     * The start node is not in the array, although the final is;
     */
     int * path;
} DjkPath;


DjkStorage *dijkstra(HexBoard *board, int start, int final,
    unsigned char c_mask, int noneWeight, int blackWeight, int whiteWeight);
void djkDestroy(DjkStorage *djkS);
DjkPath *djkGetPath(DjkStorage *storage, int final);
void djkDestroyPath(DjkPath *path);
void djkPrintPath(DjkPath *path);


/* Calcula o menor caminho para um Node, ou para todos os Nodes no HexBoard,
 * usando apenas hexágonos que combinam com a c_mask!
 * args: start: O hexágono inicial
 *       final: Hexágono final, ou uma posição inválida (como id < 0) para
 *              calcular o caminho de tods os Nodes.
 *       c_mask: Bitmask das cores para saber em quais Nodes é o algoritmo
 *               pode percorrer (ver verifyColorsMask).
 */
 /* Impl https://pt.wikipedia.org/wiki/Algoritmo_de_Dijkstra */

DjkStorage *dijkstra(HexBoard *board, int start, int final,
    unsigned char c_mask, int noneWeight, int blackWeight, int whiteWeight) {
    int hexCount, i, QNb, u, *dist, *previous, *n_Nodes, *v;
    s_Int *Q;

    if(!isHexagonValid(start, board)) {
        printf("[Dijkstra] Posição inválida do Hexagon! D:\n");
        /* TODO: finish the function here?? */
    }

    hexCount = getHexagonsCount(board);
    dist = emalloc(sizeof(int)*hexCount);
    previous = emalloc(sizeof(int)*hexCount);
    n_Nodes = emalloc(sizeof(int)*hexCount);
    Q = emalloc(sizeof(int)*hexCount);
    QNb = 0;

    for(i=0; i < hexCount; i++) {
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
        u = chooseInQ_SmallestDistance(Q, dist, cellsNb, hexgrid, colorsMask);

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



    }

    /** Main Loop **/
    while(QNb>0) {


        // Get neighbors of u
        int * v = hexgrid_getCellNeighbors(u, hexgrid);

        // Foreach neighbors v[i] of u
        for(i=0; i<hexgrid_getCellNeighborsNumber(u, hexgrid); i++) {
            // Does v[i] exist ? Maybe we're near a border of the graph or outside
            if(v[i]<0) {
                continue;
            }

            // v[i] has to be in Q; otherwise we already explored it or it's not reachable because of colorMask ...
            if(Q[v[i]]==0) {
                continue;
            }

            // v[i] has to match our colorsMask or be a border, otherwise we can't walk on it
            if(verifyColorsMask(hexgrid, v[i], colorsMask)==0) {
                continue;
            }

            // Compute the distance from source to v[i]. In the HexGrid, every x->y distance == 1
            int alt = 0;
            if     (hexgrid_getCellColor(v[i], hexgrid)==WHITE)    alt = dist[u] + whiteWeight;
            else if(hexgrid_getCellColor(v[i], hexgrid)==BLACK)       alt = dist[u] + blackWeight;
            else                                                    alt = dist[u] + blankWeight;

            // If the new path is shorter than the previously found
            if(alt<dist[v[i]]) {
                dist[v[i]] = alt;
                previous[v[i]] = u;
                Q[v[i]] = 1;
                nbOfNodes[v[i]] = nbOfNodes[u] + 1;
            }
        }

        // Free the neighbors
        free(v);
    }

    free(Q);

    // Create the result
    DijkstraResult * result = malloc(sizeof(DijkstraResult));
    result->hexgrid = hexgrid;
    result->source = source;
    result->destination = destination;
    result->colorsMask = colorsMask;
    result->dist = dist;
    result->previous = previous;
    result->nbOfNodes = nbOfNodes;

    // Print the results
    //dijkstra_print(result);

    return result;
}


/* Retorna o Node em 'Q' que possui a menor distância e combina com a c_mask,
 * além de considerar caso seja uma borda.
 */
/*
 * Q = Um conjunto de Nodes , possui Nodes na c_mask
 * dist = Array com a distância dos Nodes
 * hexCount = Número de hexágonos em Q e em dist
 * hexBoard = O tabuleiro hexagonal para procurar as cores
 * c_mask = Bitmask com as cores aceitas
 */

int getMinDistance_Q(s_Int *Q, int *dist, int hexCount, hexBoard *board,
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
dok
