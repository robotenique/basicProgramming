#ifndef __STABLE_VD_H__
#define __STABLE_VD_H__
#include "arrayOps.h"

typedef struct stable_s *SymbolTableVD;

SymbolTableVD createST_VD();
void destroyST_VD(SymbolTableVD table);
InsertionResult insertST_VD(SymbolTableVD table, const char *key);
int applyST_VD(SymbolTableVD table,
            int (*apply)(const char *key, EntryData *data, word *arr, int i),
            word *arr);


#endif
