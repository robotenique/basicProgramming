#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "tabelaSimbolo_LD.h"
#include "arrayOps.h"

typedef struct entryST {
    char *key;
    EntryData data;
    struct entryST *next;
} Entry;

struct stable_s {
    Entry *head;
};

SymbolTableLD createST_LD() {
    SymbolTableLD t = emalloc(sizeof(struct stable_s));
    t -> head = NULL;
    return t;
}

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

InsertionResult insertST_LD(SymbolTableLD table, const char *key) {
    InsertionResult ir;
    Entry *p, *new;
    ir.new = 0;
    for (p = table->head; p != NULL; p = p->next) {
        if (strcmp(p->key, key) == 0) {
            ir.data = &(p->data);
            return ir;
        }
    }
    new = emalloc(sizeof(Entry));
    new->key = estrdup(key);
    new->data.i = 0;
    new->next = table->head;
    table->head = new;
    ir.new = 1;
    ir.data = &(new->data);
    return ir;
}

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
