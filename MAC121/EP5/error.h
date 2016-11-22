#ifndef __ERROR_H__
#define __ERROR_H__
/*
 * Função: emalloc
 * --------------------------------------------------------
 * Executa um malloc, porém termina a execução do programa se não
 * foi possível alocar memória.
 * @args    size: tamanho para alocar
 *
 * @return ponteiro para a memória alocada.
 */
void * emalloc(int size);

#endif
