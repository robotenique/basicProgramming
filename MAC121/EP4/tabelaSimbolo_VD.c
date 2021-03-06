/*
 * @author: Juliano Garcia de Oliveira
 * nº usp = 9277086
 * MAC0121
 * 14/11/2016
 * Implementação da tabela de símbolos usando um vetor desordenado.
 */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "tabelaSimbolo_VD.h"
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

/*
 * Função: createST_VD
 * --------------------------------------------------------
 * Cria a tabela de símbolos (VD). No caso de um vetor desordenado,
 * aloca a estrutura, o vetor de palavras e o vetor de chaves, sendo que 'i'
 * recebe 0 para indicar que a tabela está vazia.
 *
 * @args
 *
 * @return Uma tabela de símbolos (VD) vazia.
 */
SymbolTableVD createST_VD() {
    /* Tamanho inicial máximo */
    int iniMax = 1024;
    SymbolTableVD t;
    t = emalloc(sizeof(stable_s));
    t->i = 0;
    t->max = iniMax;
    t->values = calloc(iniMax ,sizeof(EntryData));
    if(t->values == NULL) die("Error in memory allocation!");
    t->keys = emalloc(iniMax*sizeof(char *));
    return t;
}

/*
 * Função: destroyST_VD
 * --------------------------------------------------------
 * Libera toda a memória alocada pela tabela de símbolos (VD),
 * percorrendo cada elemento dos vetores das chaves e liberando a memória, em
 * seguida liberando todos os outros vetores.
 *
 * @args    table: Tabela de símbolos (VD)
 *
 * @return
 */
void destroyST_VD(SymbolTableVD table) {
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
 * Realoca a tabela de símbolos (VD), copiando os dados da tabela de símbolos
 * atual para uma nova com o dobro de tamanho.
 *
 * @args    t:  Tabela de Símbolos (VD)
 *
 * @return
 */
void reallocST_VD(SymbolTableVD t) {
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
 * Função: insertST_VD
 * --------------------------------------------------------
 * Função que insere um elemento na primeira posição livre 'i' da tabela de
 * símbolos (VD) se o elemento não estiver na tabela. Se estiver, o elemento
 * não é inserido.
 *
 * @args    table: Tabela de Símbolos (VD)
 *          key:   Nova chave para ser inserida na tabela
 *
 * @return Um Insertion Result com os dados da inserção.
 */
InsertionResult insertST_VD(SymbolTableVD table, const char *key) {
    InsertionResult ir;
    int pos;
    char* cpy;
    ir.new = 0;
    cpy = estrdup(key);
    pos = linearSearch(table -> keys, cpy, table -> i);
    /* Se o elemento estiver na tabela */
    if(pos >= 0) {
        ir.data = &(table -> values[pos]);
        free(cpy);
        return ir;
    }
    /* Se o elemento não está na tabela */
    else {
        ir.new = 1;
        if (table -> i >= table -> max)
            reallocST_VD(table);
        table->keys[table->i] = cpy;
        ir.data = &(table -> values[table->i]);
        table->i = (table->i) + 1;
    }
        return ir;
}

/*
 * Função: applyST_VD
 * --------------------------------------------------------
 * Para cada elemento da tabela de símbolos (VD), aplica a função 'apply'.
 *
 * @args    table:  Tabela de símbolos (VD)
 *          apply:  Ponteiro para a função
 *          arr:    Ponteiro para um array de pares {palavra:frequência}
 *
 * @return 0 se a função foi interrompida pela 'apply', 1 caso contrário
 */
int applyST_VD(SymbolTableVD table,
            int (*apply)(const char *key, EntryData *data, word *arr, int i),
            word *arr) {
    int i;
    for (i = 0; i < table->i; i++)
        if(!apply(table->keys[i], &(table->values[i]), arr, i))
            return 0;
    return 1;
}
