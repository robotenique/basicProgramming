/*
 * @author: Juliano Garcia de Oliveira
 * nº usp = 9277086
 * MAC0121
 * 14/11/2016
 * Arquivo header com funções para calcular a frequência usando
 * tabelas de símbolos de diferentes implementações.
 */
#ifndef __FREQUENCIA_CALC_H__
#define __FREQUENCIA_CALC_H__
/*
 * Função: calculateFreqVD
 * --------------------------------------------------------
 * Calcula a frequência de palavras contidas no arquivo 'input' e as ordena
 * de acordo com a configuração de entrada passada como argumento, usando
 * uma tabela de símbolos implementada usando um vetor desordenado.
 * Em seguida, imprime as palavras e suas respectivas frequências.
 *
 * @args    input:  Arquivo para leitura das palavras
 *          conf:   Struct que contém informação de como ordenar as palavras
 *
 * @return
 */
void calculateFreqVD (FILE *input, inputConfig conf);
/*
 * Função: calculateFreqVO
 * --------------------------------------------------------
 * Calcula a frequência de palavras contidas no arquivo 'input' e as ordena
 * de acordo com a configuração de entrada passada como argumento, usando
 * uma tabela de símbolos implementada usando um vetor ordenado.
 * Em seguida, imprime as palavras e suas respectivas frequências.
 *
 * @args    input:  Arquivo para leitura das palavras
 *          conf:   Struct que contém informação de como ordenar as palavras
 *
 * @return
 */
void calculateFreqVO (FILE *input, inputConfig conf);
/*
 * Função: calculateFreqLD
 * --------------------------------------------------------
 * Calcula a frequência de palavras contidas no arquivo 'input' e as ordena
 * de acordo com a configuração de entrada passada como argumento, usando
 * uma tabela de símbolos implementada usando uma lista ligada desordenada.
 * Em seguida, imprime as palavras e suas respectivas frequências.
 *
 * @args    input:  Arquivo para leitura das palavras
 *          conf:   Struct que contém informação de como ordenar as palavras
 *
 * @return
 */
void calculateFreqLD (FILE *input, inputConfig conf);
/*
 * Função: calculateFreqLO
 * --------------------------------------------------------
 * Calcula a frequência de palavras contidas no arquivo 'input' e as ordena
 * de acordo com a configuração de entrada passada como argumento, usando
 * uma tabela de símbolos implementada usando uma lista ligada ordenada.
 * Em seguida, imprime as palavras e suas respectivas frequências.
 *
 * @args    input:  Arquivo para leitura das palavras
 *          conf:   Struct que contém informação de como ordenar as palavras
 *
 * @return
 */
void calculateFreqLO (FILE *input, inputConfig conf);
/*
 * Função: calculateFreqAB
 * --------------------------------------------------------
 * Calcula a frequência de palavras contidas no arquivo 'input' e as ordena
 * de acordo com a configuração de entrada passada como argumento, usando
 * uma tabela de símbolos implementada usando uma árvore de busca binária.
 * Em seguida, imprime as palavras e suas respectivas frequências.
 *
 * @args    input:  Arquivo para leitura das palavras
 *          conf:   Struct que contém informação de como ordenar as palavras
 *
 * @return
 */
void calculateFreqAB (FILE *input, inputConfig conf);
#endif
