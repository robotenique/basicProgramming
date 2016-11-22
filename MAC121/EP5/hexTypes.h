#ifndef _HEX_TYPES_H_
#define _HEX_TYPES_H_
#include <stdlib.h>
#define N_SIZE 14

/* Simple type definition */
typedef enum { false, true } bool;
typedef enum { NONE, WHITE, BLACK } color;
typedef unsigned short int s_Int;

/* Structures definition */
typedef struct {
    s_Int color; /* Can be NONE, WHITE or BLACK */
} Hexagon;

typedef struct {
    s_Int size; /* The size n of the grid (we use n = 14) */
    color player; /* The player to play */
    Hexagon *hexs; /* The hexagons of the grid */
} HexBoard;

#endif
