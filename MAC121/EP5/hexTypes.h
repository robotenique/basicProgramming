/*
 * @author: Juliano Garcia de Oliveira
 * nº usp = 9277086
 * MAC0121
 * 28/11/2016
 * Header que contém tipos simples usados no jogo
 */
#ifndef _HEX_TYPES_H_
#define _HEX_TYPES_H_
#include <stdlib.h>
#define N_SIZE 14 /* O tamanho é pré-definido */

/* Tipos simples */
typedef enum { false, true } bool;
typedef enum { NONE, WHITE, BLACK, INVALID } color;
typedef unsigned short int s_Int;

/* Variável global que sinaliza o debug */
bool debug;
#endif
