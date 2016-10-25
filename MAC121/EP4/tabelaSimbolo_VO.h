#ifndef __STABLE_VO_H__
#define __STABLE_VO_H__
#include "arrayOps.h"

typedef struct stable_s *SymbolTableVO;

SymbolTableVO createST_VO();


void destroyST_VO(SymbolTableVO table);

InsertionResult insertST_VO(SymbolTableVO table, const char *key);

int applyST_VO(SymbolTableVO table,
            int (*apply)(const char *key, EntryData *data, word *arr, int i),
            word *arr);

#endif
