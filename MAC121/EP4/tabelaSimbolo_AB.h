#ifndef __STABLE_AB_H__
#define __STABLE_AB_H__
#include "arrayOps.h"

typedef struct stable_s *SymbolTableAB;

SymbolTableAB createST_AB();
void destroyST_AB(SymbolTableAB table);
InsertionResult insertST_AB(SymbolTableAB table, const char *key);
void applyST_AB(SymbolTableAB table,
            void (*apply)(const char *key, EntryData *data, word_BST *arr),
            word_BST *arr);

#endif
