/*
  stable.h

  A symbol table associating generic data to strings.
*/
#include "tabelaSimbolo_VD.h"
#include "arrayOps.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
typedef struct stable_s {
    unsigned char** keys;
	EntryData* values;
    unsigned int i;
    unsigned int max;
} stable_s;
/*
  Return a new symbol table.
*/
SymbolTableVD stable_create() {
    int iniMax = 1024;
    SymbolTableVD t = emalloc(sizeof(stable_s));
    t -> i = 0;
    t -> max = iniMax;
    t -> values = emalloc(iniMax * sizeof(EntryData));
    t -> keys = emalloc(iniMax * sizeof(unsigned char*));
    return t;
}

/*
  Destroy a given symbol table.
*/
void stable_destroy(SymbolTableVD table) {
    free(table -> values);
    for (int i = 0; i < table->i; i++)
        free(table->keys[i]);
    free(table -> keys);
    free(table);
}

void reallocStable(SymbolTableVD t) {

    unsigned char** ktemp = emalloc((t->max)*2*sizeof(unsigned char*));
    EntryData* vtemp = emalloc((t->max)*2*sizeof(EntryData));
    // Copy the old values
    for (int i = 0; i < t -> i; i++) {
        vtemp[i] = t->values[i];
        ktemp[i] = t->keys[i];
    }
    free(t->values);
    free(t->keys);
    t->keys = ktemp;
    t->values = vtemp;
    t->max = (t->max)*2;
}

// Check if a key is in the 'keys' array
int linearSearch (unsigned char **keys, unsigned char* str, int n) {
    for (int i = 0; i < n; i++) {
       if (strcmp(keys[i], str) == 0)
           return i;
   }
   // We didn't find the str in the keys array
   return -1;
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
InsertionResult stable_insert(SymbolTableVD table, const unsigned char *key) {
    InsertionResult ir;
    ir.new = 0;
    //Careful
    unsigned char* cpy = emalloc(strlen(key));
    strcpy(cpy, key);
    //Linear search
    int pos = linearSearch(table -> keys, cpy, table -> i);
    if(pos >= 0) {
        ir.data = &(table -> values[pos]);
        return ir;
    }
    else {
        ir.new = 1;
        if (table -> i >= table -> max)
            reallocStable(table);
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
EntryData *stable_find(SymbolTableVD table, const unsigned char *key) {
    unsigned char* cpy = emalloc(strlen(key));
    strcpy(cpy, key);
    int pos = linearSearch(table->keys, cpy, table-> i);
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
int stable_visit(SymbolTableVD table,
                 int (*visit)(const unsigned char *key, EntryData *data)) {
         for (int i = 0; i < table->i; i++)
                 if(!visit(table->keys[i], &(table->values[i])))
                 return 0;
            return 1;
}
