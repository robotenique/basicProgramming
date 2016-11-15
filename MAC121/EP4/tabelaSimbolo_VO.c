/*
 * @author: Juliano Garcia de Oliveira
 * nº usp = 9277086
 * MAC0121
 * 14/11/2016
 * Implementação da tabela de símbolos usando um vetor ordenado.
 */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "tabelaSimbolo_VO.h"
#include "arrayOps.h"

/* A tabela de símbolos contém:
 * keys: Um array com as chaves
 * values: Um array com os valores
 * i: Pŕóxima posição livre
 * max: Máximo de elementos disponível na tabela
 */
typedef struct stable_s {
    char** keys;
	EntryData* values;
    unsigned int i;
    unsigned int max;
} stable_s;

int bSearchRec (char *keys[], char *target, int b, int t);

/*
 * Função: createST_VO
 * --------------------------------------------------------
 * Cria a tabela de símbolos (VO). No caso de um vetor ordenado,
 * aloca a estrutura, o vetor de palavras e o vetor de chaves, sendo que 'i'
 * recebe 0 para indicar que a tabela está vazia.
 *
 * @args
 *
 * @return Uma tabela de símbolos (VO) vazia.
 */
SymbolTableVO createST_VO() {
    int iniMax = 1024;
    SymbolTableVO t;
    t = emalloc(sizeof(stable_s));
    t -> i = 0;
    t -> max = iniMax;
    t -> values = calloc(iniMax ,sizeof(EntryData));
    if(t -> values == NULL) die("Error in memory allocation!");
    t -> keys = emalloc(iniMax * sizeof(char*));
    return t;
}

/*
 * Função: destroyST_VO
 * --------------------------------------------------------
 * Libera toda a memória alocada pela tabela de símbolos (VO),
 * percorrendo cada elemento dos vetores das chaves e liberando a memória, em
 * seguida liberando todos os outros vetores.
 *
 * @args    table: Tabela de símbolos (VO)
 *
 * @return
 */
void destroyST_VO(SymbolTableVO table) {
    int i;
    free(table -> values);
    for (i = 0; i < table->i; i++)
        free(table->keys[i]);
    free(table -> keys);
    free(table);
}

/*
 * Função: reallocST_VD
 * --------------------------------------------------------
 * Realoca a tabela de símbolos (VO), copiando os dados da tabela de símbolos
 * atual para uma nova com o dobro de tamanho.
 *
 * @args    t:  Tabela de Símbolos (VO)
 *
 * @return
 */
void reallocST_VO(SymbolTableVO t) {
    char** ktemp;
    EntryData* vtemp;
    int i;
    ktemp = emalloc((t->max)*2*sizeof(char*));
    vtemp = calloc((t->max)*2,sizeof(EntryData));
    if(vtemp == NULL) die("Error in memory allocation!");
    /* Copy the old values */
    for (i = 0; i < t -> i; i++) {
        vtemp[i] = t->values[i];
        ktemp[i] = t->keys[i];
    }
    free(t->values);
    free(t->keys);
    t->keys = ktemp;
    t->values = vtemp;
    t->max = (t->max)*2;
}

/*
 * Função: bSearchRec
 * --------------------------------------------------------
 * Busca binária recursiva, que procura uma chave na tabela de símbolos,
 * já que ela está ordenada.
 *
 * @args    keys: Vetor das chaves da tabela de símbolos
 *          target: Palavra para buscar na tabela de símbolos
 *          b: O "bottom" ou "início" do vetor para a busca binária
 *          t: O "top" ou "fim" do vetor para a busca binária
 *
 * @return  Retorna o "top" ("end") se  não encontrou, caso contrário retorna
 *          a posição onde foi encontrado no vetor.
 */
int bSearchRec (char *keys[], char *target, int b, int t) {
    int m, cmp;
    /* Se o bottom > top, então não encontrou o elemento */
    if (b > t)
        return t;
    m = (b + t)/2;
    cmp = strcmp(keys[m], target);
    if (!cmp)
        return m;
    if(cmp > 0)
        return bSearchRec(keys, target, b, m - 1);
    return bSearchRec(keys, target, m + 1, t);
}

/*
 * Função: insertST_VO
 * --------------------------------------------------------
 * Função que insere um elemento na posição correta da tabela de
 * símbolos (VO), de modo a manter a tabela ordenada, se o elemento não estiver
 * na tabela. Se estiver, o elemento não é inserido.
 *
 * @args    table: Tabela de Símbolos (VO)
 *          key:   Nova chave para ser inserida na tabela
 *
 * @return Um Insertion Result com os dados da inserção.
 */
InsertionResult insertST_VO(SymbolTableVO table, const char *key) {
    InsertionResult ir;
    int pos = 0, k = 0;
    char* cpy;
    ir.new = 1;
    cpy = estrdup(key);
    /* Faz a busca binária na tabela */
    pos = bSearchRec(table->keys, cpy, 0, table->i - 1);
    if(pos >= 0)
        if(!strcmp(table->keys[pos], key)) {
            ir.new = 0;
            ir.data = &(table->values[pos]);
            free(cpy);
            return ir;
        }

    /* Se a tabela está cheia, chama a função para realocar */
    if(table->i + 1 >= table->max)
        reallocST_VO(table);
    /* Desloca os elementos para frente */
    for (k = table->i - 1; k > pos; k--) {
        table->keys[k + 1] = table->keys[k];
        table->values[k + 1] = table->values[k];
    }
    table->keys[pos + 1] = cpy;
    ir.data = &(table->values[pos + 1]);
    table->i += 1;
    return ir;
}

/*
 * Função: applyST_VO
 * --------------------------------------------------------
 * Para cada elemento da tabela de símbolos (VO), aplica a função 'apply'.
 *
 * @args    table:  Tabela de símbolos (VO)
 *          apply:  Ponteiro para a função
 *          arr:    Ponteiro para um array de pares {palavra:frequência}
 *
 * @return 0 se a função foi interrompida pela 'apply', 1 caso contrário
 */
int applyST_VO(SymbolTableVO table,
            int (*apply)(const char *key, EntryData *data, word *arr, int i),
            word *arr) {
    int i;
    for (i = 0; i < table->i; i++)
        if(!apply(table->keys[i], &(table->values[i]), arr, i))
            return 0;
    return 1;
}
