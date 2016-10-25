/*
  stable.h

  A symbol table associating generic data to strings.
*/
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "tabelaSimbolo_VD.h"
#include "arrayOps.h"

typedef struct stable_s {
    char** keys;
	EntryData* values;
    unsigned int i;
    unsigned int max;
} stable_s;

SymbolTableVD createST_VD() {
    int iniMax = 1024;
    SymbolTableVD t;
    t = emalloc(sizeof(stable_s));
    t -> i = 0;
    t -> max = iniMax;
    t -> values = calloc(iniMax ,sizeof(EntryData));
    if(t -> values == NULL) die("Error in memory allocation!");
    t -> keys = emalloc(iniMax * sizeof(char*));
    return t;
}


void destroyST_VD(SymbolTableVD table) {
    int i;
    free(table -> values);
    for (i = 0; i < table->i; i++)
        free(table->keys[i]);
    free(table -> keys);
    free(table);
}

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

InsertionResult insertST_VD(SymbolTableVD table, const char *key) {
    InsertionResult ir;
    int pos;
    char* cpy;
    ir.new = 0;
    cpy = estrdup(key);
    pos = linearSearch(table -> keys, cpy, table -> i);
    if(pos >= 0) {
        ir.data = &(table -> values[pos]);
        free(cpy);
        return ir;
    }
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

int applyST_VD(SymbolTableVD table,
            int (*apply)(const char *key, EntryData *data, word *arr, int i),
            word *arr) {
        int i;
        for (i = 0; i < table->i; i++)
                if(!apply(table->keys[i], &(table->values[i]), arr, i))
                return 0;
        return 1;
}
