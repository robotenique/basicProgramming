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

EntryData* insertLinkedL(Entry ** head, char *key) {
    Entry *new;
    EntryData *irPointer;
    new = emalloc(sizeof(Entry));
    new->key = key;
    /* Initialize the bigger type of union with zero */
    new->data.i = 0;
    irPointer = &(new->data);
    new->next = *head;
    *head = new;
    return irPointer;
}

Entry * searchLD(Entry * head, char *key) {
    /* Return NULL if value is x is not in the list */
    Entry * p;
    for (p = head; p && strcmp(p->key, key); p = p->next);
    return p;
}

InsertionResult insertST_LD(SymbolTableLD table, const char *key) {
    InsertionResult ir;
    Entry *p;
    char *cpy;
    ir.new = 0;
    cpy = estrdup(key);
    p = searchLD(table->head, cpy);
    if(p != NULL) {
        ir.data =&(p->data);
        free(cpy);
        return ir;
    }
    ir.new = 1;
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
