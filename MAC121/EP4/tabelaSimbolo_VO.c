/*
  stable.h

  A symbol table associating generic data to strings.
*/
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
    bool ordFreq;
} stable_s;
/*
  Return a new symbol table.
*/
SymbolTableVO stable_createVO(bool sortByFreq) {
    int iniMax = 1024;
    SymbolTableVO t;
    t = emalloc(sizeof(stable_s));
    t -> i = 0;
    t -> max = iniMax;
    t -> values = calloc(iniMax ,sizeof(EntryData));
    if(t -> values == NULL) die("Error in memory allocation!");
    t -> keys = emalloc(iniMax * sizeof(char*));
    t -> ordFreq = sortByFreq;
    return t;
}

/*
  Destroy a given symbol table.
*/
void stable_destroyVO(SymbolTableVO table) {
    int i;
    free(table -> values);
    for (i = 0; i < table->i; i++)
        free(table->keys[i]);
    free(table -> keys);
    free(table);
}

void reallocStableVO(SymbolTableVO t) {
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
  Insert a new entry on the symbol table given its key.

  If there is already an entry with the given key, then a struct
  InsertionResult is returned with new == 0 and data pointing to the
  data associated with the entry. Otherwise, a struct is returned with
  new != 0 and data pointing to the data field of the new entry.

  If there is not enough space on the table, or if there is a memory
  allocation error, then crashes with an error message.
*/
InsertionResult stable_insertVO(SymbolTableVO table, const char *key) {
    InsertionResult ir;
    int pos;
    char* cpy;
    ir.new = 0;
    cpy = estrdup(key);
    /*Linear search*/
    pos = linearSearch(table -> keys, cpy, table -> i);
    if(pos >= 0) {
        ir.data = &(table -> values[pos]);
        free(cpy);
        return ir;
    }
    else {
        ir.new = 1;
        if (table -> i >= table -> max)
            reallocStableVO(table);
        table->keys[table->i] = cpy;
        ir.data = &(table -> values[table->i]);
        table->i = (table->i) + 1;
    }
        return ir;
}

/*
  Find the data associated with a given key.

  Given a key, returns a pointer to the data associated with it, or a
  NULL pointer if the key is not found.
*/
EntryData *stable_findVO(SymbolTableVO table, const char *key) {
    char* cpy;
    int pos;
    cpy = emalloc(strlen(key));
    strcpy(cpy, key);
    pos = linearSearch(table->keys, cpy, table-> i); /*Bsort*/
    if(pos >= 0)
        return &(table->values[pos]);
    else
        return NULL;
}

/*
  Visit each entry on the table.

  The visit function is called on each entry, with pointers to its key
  and data. If the visit function returns zero, then the iteration
  stops.

  Returns zero if the iteration was stopped by the visit function,
  nonzero otherwise.
*/
int stable_visitVO(SymbolTableVO table,
            int (*visit)(const char *key, EntryData *data, word *arr, int i),
            word *arr) {
        int i;
        for (i = 0; i < table->i; i++)
                if(!visit(table->keys[i], &(table->values[i]), arr, i))
                return 0;
        return 1;
}
