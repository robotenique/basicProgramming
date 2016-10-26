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
    int max;
    int i;
    Entry *entries;
    Entry *head;
};


SymbolTableLD createST_LD() {
    int iniMax = 1;
    SymbolTableLD t = emalloc(sizeof(struct stable_s));
    t -> i = 0;
    t -> max = iniMax;
    t -> head = NULL;
    return t;
}

EntryData* insertLinkedL(Entry ** head, char *key) {
    Entry * new;
    EntryData * irPointer;
    new = emalloc(sizeof(Entry));
    new->key = estrdup(key);
    irPointer = &(new->data);
    new->next = *head;
    *head = new;
    return irPointer;
}

Entry * searchLinkedL(Entry * head, char *key) {
    /* Return NULL if value is x is not in the list */
    Entry * p;
    for (p = head; p != NULL && strcmp(p->key, key); p = p->next);
    return p;
}


InsertionResult insertST_LD(SymbolTableLD table, const char *key) {
    InsertionResult ir;
    Entry *p;
    char *cpy;
    ir.new = 0;
    cpy = estrdup(key);
    p = searchLinkedL(table->head, cpy);
    if(p != NULL) {
        ir.data =&(p->data);
        free(cpy);
        return ir;
    }
    ir.new = 1;
    table->i += 1;
    ir.data = insertLinkedL(&(table->head), cpy);
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
