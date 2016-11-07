/*
 * @author: Juliano Garcia de Oliveira
 * nº usp = 9277086
 * MAC0121
 * 14/11/2016
 * Header file para criar um buffer, usando o modelo de
 * estruturas de dados ensinado em Técnicas de Programação I (MAC216)
 */
#ifndef __BUFFER_H__
#define __BUFFER_H__
#include <stdio.h>
#include <ctype.h>
#include "arrayOps.h"
#include <stdlib.h>

/* Estrutura que contém o buffer */
typedef struct buffer_s {
  char *data;
  int n; /* Valor máximo de caracteres do Buffer */
  int i; /* Próxima posição livre do bufer */
} Buffer;

/*
 * Função: buffer_create
 * --------------------------------------------------------
 * Aloca um buffer e retorna um ponteiro para a estrutura.
 *
 * @args
 *
 * @return Ponteiro para um buffer.
 */
Buffer * buffer_create();

/*
 * Função: buffer_destroy
 * --------------------------------------------------------
 * Destrói um Buffer, liberando a memória
 *
 * @args    B: Ponteiro para um Buffer
 *
 * @return
 */
void buffer_destroy(Buffer *B);

/*
 * Função: buffer_reset
 * --------------------------------------------------------
 * Faz um Buffer voltar ao estado original, alocando novamente
 * um array de chars e voltando o apontador 'i' para o início.
 *
 * @args    B: Ponteiro para um Buffer
 *
 * @return
 */
void buffer_reset(Buffer *B);

/*
 * Função: buffer_push_back
 * --------------------------------------------------------
 * Adiciona o char C no final do Buffer. (Lembrar que o buffer é uma
 * estrutura FIFO)
 *
 * @args    B:  Ponteiro para um Buffer
 *          c:  Caractere para ser inserido no Buffer
 *
 * @return
 */
void buffer_push_back(Buffer *B, char c);

/*
 * Função: read_line
 * --------------------------------------------------------
 * Lê uma linha do arquivo passado como argumento, até encontrar um '\n'
 * ou o EOF. Caso haja um '\n', ele é inserido no Buffer também.
 *
 * @args    input: Ponteiro para um Arquivo
 *          B:  Ponteiro para um Buffer
 *
 * @return  o número de caracteres lido, ou 0 se não leu nenhum (i.e. encontrou
 * EOF antes de ler algum caractere)
 */
int read_line(FILE *input, Buffer *B);

/*
 * Função: buffer_lower
 * --------------------------------------------------------
 * Transforma todos os caracteres do Buffer em minúsculo
 *
 * @args    B: Ponteiro para um Buffer
 *
 * @return
 */
void buffer_lower(Buffer *B);

#endif
