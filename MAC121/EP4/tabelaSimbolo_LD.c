/*
 * @author: Juliano Garcia de Oliveira
 * nº usp = 9277086
 * MAC0121
 * 14/11/2016
 * Implementação da tabela de símbolos usando Lista ligada desordenada.
 */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "tabelaSimbolo_LD.h"
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
 * Função: createST_LD
 * --------------------------------------------------------
 * Cria a tabela de símbolos (LD). No caso de uma lista ligada,
 * só aloca a estrutura de dado e faz com que a cabeça receba NULL, indicando
 * que a tabela está vazia.
 *
 * @args
 *
 * @return Uma tabela de símbolos (LD) vazia.
 */
SymbolTableLD createST_LD() {
    SymbolTableLD t = emalloc(sizeof(struct stable_s));
    t->head = NULL;
    return t;
}

/*
 * Função: destroyST_LD
 * --------------------------------------------------------
 * Libera toda a memória alocada pela tabela de símbolos (LD),
 * percorrendo cada elemento da lista ligada e liberando-o da memória alocada.
 *
 * @args    table: Tabela de símbolos (LD)
 *
 * @return
 */
void destroyST_LD(SymbolTableLD table) {
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
 * Função: insertST_LD
 * --------------------------------------------------------
 * Função que insere um elemento na primeira posição da tabela de símbolos (LD)
 * se o elemento não estiver na tabela. Se estiver, o elemento não é inserido.
 *
 * @args    table: Tabela de Símbolos (LD)
 *          key:   Nova chave para ser inserida na tabela
 *
 * @return Um Insertion Result com os dados da inserção.
 */
InsertionResult insertST_LD(SymbolTableLD table, const char *key) {
    InsertionResult ir;
    Entry *p, *ant, *new;
    ir.new = 0;
    /* Busca linear na lista ligada */
    for (ant = NULL, p = table->head; p != NULL; ant = p, p = p->next) {
        /* Se o elemento foi encontrado, para o loop */
        if (strcmp(p->key, key) == 0) {
            ir.data = &(p->data);
            return ir;
        }
    }
    /* Se o elemento não foi encontrado, cria uma nova entrada na tabela de
     *  símbolos e coloca no início da lista ligada
     */

    new = emalloc(sizeof(Entry));
    new->key = estrdup(key);
    new->data.i = 0;
    new->next = NULL;
    if(ant != NULL)
        ant->next = new;
    else
        table->head = new;
    ir.new = 1;
    ir.data = &(new->data);
    return ir;
}

/*
 * Função: applyST_LD
 * --------------------------------------------------------
 * Para cada elemento da lista, aplica a função 'apply'.
 *
 * @args    table:  Tabela de símbolos (LD)
 *          apply:  Ponteiro para a função
 *          arr:    Ponteiro para um array de pares {palavra:frequência}
 *
 * @return 0 se a função foi interrompida pela 'apply', 1 caso contrário
 */
int applyST_LD(SymbolTableLD table,
            int (*apply)(const char *key, EntryData *data, word *arr, int i),
            word *arr) {
        int i;
        Entry *p;
        for (p = table->head, i = 0; p; p = p->next, i++)
            if(!apply(p->key, &(p->data), arr, i))
                return 0;
        return 1;
}
