#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "tabelaSimbolo_LO.h"
#include "arrayOps.h"

typedef struct entryST {
    char *key;
    EntryData data;
    struct entryST *next;
} Entry;

struct stable_s {
    Entry *head;
};

SymbolTableLO createST_LO() {
    SymbolTableLO t = emalloc(sizeof(struct stable_s));
    t -> head = NULL;
    return t;
}

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

InsertionResult insertST_LO(SymbolTableLO table, const char *key) {
    InsertionResult ir;
    Entry *p, *ant, *new;
    char *cpy;
    int cmp;
    ir.new = 0;
    cpy = estrdup(key);
    p = table->head;
    ant = NULL;
    while(p != NULL && (cmp = strcmp(p->key, cpy)) < 0) {
        ant = p;
        p = p->next;
    }
    if(cmp == 0) {
        ir.data = &(p->data);
        free(cpy);
        return ir;
    }
    ir.new = 1;
    new = emalloc(sizeof(Entry));
    new->key = cpy;
    /* Initialize the bigger type of union with zero */
    new->data.i = 0;
    ir.data = &(new->data);
    if(ant == NULL) table->head = new;
    else ant->next = new;
    new->next = p;
    return ir;
}

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
