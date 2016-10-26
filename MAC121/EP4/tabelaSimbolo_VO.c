#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "tabelaSimbolo_VO.h"
#include "arrayOps.h"


typedef struct stable_s {
    char** keys;
	EntryData* values;
    unsigned int i;
    unsigned int max;
} stable_s;

int bSearchRec (char *keys[], char *target, int b, int t);

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

void destroyST_VO(SymbolTableVO table) {
    int i;
    free(table -> values);
    for (i = 0; i < table->i; i++)
        free(table->keys[i]);
    free(table -> keys);
    free(table);
}

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

InsertionResult insertST_VO(SymbolTableVO table, const char *key) {
    InsertionResult ir;
    int pos = 0, k = 0;
    char* cpy;
    ir.new = 1;
    cpy = estrdup(key);
    /*Executing binary search*/
    pos = bSearchRec(table->keys, cpy, 0, table->i - 1);
    if(pos >= 0)
        if(!strcmp(table->keys[pos], key)) {
            ir.new = 0;
            ir.data = &(table->values[pos]);
            free(cpy);
            return ir;
        }

    if(table->i + 1 >= table->max)
        reallocST_VO(table);
    for (k = table->i - 1; k > pos; k--) {
        table->keys[k + 1] = table->keys[k];
        table->values[k + 1] = table->values[k];
    }
    table->keys[pos + 1] = cpy;
    ir.data = &(table->values[pos + 1]);
    table->i += 1;
    return ir;
}

int applyST_VO(SymbolTableVO table,
            int (*apply)(const char *key, EntryData *data, word *arr, int i),
            word *arr) {
        int i;
        for (i = 0; i < table->i; i++)
                if(!apply(table->keys[i], &(table->values[i]), arr, i))
                    return 0;
        return 1;
}
