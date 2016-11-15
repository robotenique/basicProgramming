/*
 * @author: Juliano Garcia de Oliveira
 * nº usp = 9277086
 * MAC0121
 * 14/11/2016
 * Implementação da tabela de símbolos usando Lista ligada ordenada.
 */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "tabelaSimbolo_LO.h"
#include "arrayOps.h"

/* Cada entrada da tabela possui:
 * key: A chave da tabela de símbolos, é sempre única.
 * data: O dado da respectiva chave.
 * next: ponteiro para a próxima entrada.
 */
typedef struct entryST {
    char *key;
    EntryData data;
    struct entryST *next;
} Entry;

/* A tabela de símbolos contém o ponteiro para a primeira
 * entrada da tabela (a cabeça / HEAD).
 */
struct stable_s {
    Entry *head;
};

/*
 * Função: createST_LO
 * --------------------------------------------------------
 * Cria a tabela de símbolos (LO). No caso de uma lista ligada,
 * só aloca a estrutura de dado e faz com que a cabeça receba NULL, indicando
 * que a tabela está vazia.
 *
 * @args
 *
 * @return Uma tabela de símbolos (LO) vazia.
 */
SymbolTableLO createST_LO() {
    SymbolTableLO t = emalloc(sizeof(struct stable_s));
    t -> head = NULL;
    return t;
}

/*
 * Função: destroyST_LO
 * --------------------------------------------------------
 * Libera toda a memória alocada pela tabela de símbolos (LO),
 * percorrendo cada elemento da lista ligada e liberando-o da memória alocada.
 *
 * @args    table: Tabela de símbolos (LO)
 *
 * @return
 */
void destroyST_LO(SymbolTableLO table) {
    Entry *next, *head;
    head = table->head;
    for (;head; head = next) {
        next = head->next;
        free(head->key);
        free(head);
    }
    free(table);
}

/*
 * Função: insertST_LO
 * --------------------------------------------------------
 * Função que insere um elemento de forma a manter a ordem na tabela de símbolos (LO) se o elemento
 * não estiver na tabela. Se estiver, o elemento não é inserido.
 *
 * @args    table: Tabela de Símbolos (LO)
 *          key:   Nova chave para ser inserida na tabela
 *
 * @return Um Insertion Result com os dados da inserção.
 */
InsertionResult insertST_LO(SymbolTableLO table, const char *key) {
    InsertionResult ir;
    Entry *p, *ant, *new;
    ir.new = 0;
    p = table->head;
    ant = NULL;
    /* Percorre a tabela enquanto as chaves são menores que
     * 'key'.
     */
    for (; p != NULL && strcmp(p->key, key) < 0; ant = p, p = p->next);
    /* Se o elemento estiver na tabela */
    if(p != NULL && strcmp(p->key, key) == 0) {
        ir.data = &(p->data);
    }
    /* Se o elemento não está na tabela, cria um novo
     * e o coloca na posição correta de forma a manter a ordem */
    else {
        ir.new = 1;
        new = emalloc(sizeof(Entry));
        new->key = estrdup(key);
        /* Initialize a union com 0 */
        new->data.i = 0;
        ir.data = &(new->data);
        if(ant == NULL) table->head = new;
        else ant->next = new;
        new->next = p;
    }
    return ir;
}

/*
 * Função: applyST_LO
 * --------------------------------------------------------
 * Para cada elemento da lista, aplica a função 'apply'.
 *
 * @args    table:  Tabela de símbolos (LO)
 *          apply:  Ponteiro para a função
 *          arr:    Ponteiro para um array de pares {palavra:frequência}
 *
 * @return 0 se a função foi interrompida pela 'apply', 1 caso contrário
 */
int applyST_LO(SymbolTableLO table,
            int (*apply)(const char *key, EntryData *data, word *arr, int i),
            word *arr) {
        int i;
        Entry *p;
        for (p = table->head, i = 0; p; p = p->next, i++)
            if(!apply(p->key, &(p->data), arr, i))
                return 0;
        return 1;
}
