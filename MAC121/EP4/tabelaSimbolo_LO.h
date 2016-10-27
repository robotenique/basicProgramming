#ifndef __STABLE_LO_H__
#define __STABLE_LO_H__
#include "arrayOps.h"

typedef struct stable_s *SymbolTableLO;

SymbolTableLO createST_LO();
void destroyST_LO(SymbolTableLO table);
InsertionResult insertST_LO(SymbolTableLO table, const char *key);
int applyST_LO(SymbolTableLO table,
            int (*apply)(const char *key, EntryData *data, word *arr, int i),
            word *arr);

#endif
