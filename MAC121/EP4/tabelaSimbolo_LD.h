/*
 * @author: Juliano Garcia de Oliveira
 * nº usp = 9277086
 * MAC0121
 * 14/11/2016
 * Header da tabela de símbolos (LD). Detalhes das funções nos arquivos
 * de implementação.
 */
#ifndef __STABLE_LD_H__
#define __STABLE_LD_H__
#include "arrayOps.h"

typedef struct stable_s *SymbolTableLD;

SymbolTableLD createST_LD();

void destroyST_LD(SymbolTableLD table);

InsertionResult insertST_LD(SymbolTableLD table, const char *key);

int applyST_LD(SymbolTableLD table,
            int (*apply)(const char *key, EntryData *data, word *arr, int i),
            word *arr);

#endif
