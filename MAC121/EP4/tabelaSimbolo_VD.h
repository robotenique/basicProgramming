/*
 * @author: Juliano Garcia de Oliveira
 * nº usp = 9277086
 * MAC0121
 * 14/11/2016
 * Header da tabela de símbolos (VD). Detalhes das funções nos arquivos
 * de implementação.
 */
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
