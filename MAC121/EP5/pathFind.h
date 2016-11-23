#ifndef _PATH_FIND_H_
#define _PATH_FIND_H_
#include "hexBoard.h"
#include "hexTypes.h"

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

#endif
