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

Entry * searchLinkedL(Entry * head, char *key) {
    /* Return NULL if value is x is not in the list */
    Entry * p;
    for (p = head; p != NULL && strcmp(p->key, key); p = p->next);
    return p;
}

InsertionResult insertST_LD(SymbolTableLD table, const char *key) {
    Entry *p;
    char *cpy;
    cpy = estrdup(key);
    p = searchLinkedL(table->head, cpy);
    if(p != NULL)


    printf("KEY: %s , p = %p\n",key, (void *)p);
    exit(-1);
}
