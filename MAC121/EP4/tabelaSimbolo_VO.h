/*
 * @author: Juliano Garcia de Oliveira
 * nº usp = 9277086
 * MAC0121
 * 14/11/2016
 * Header da tabela de símbolos (VO). Detalhes das funções nos arquivos
 * de implementação.
 */
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
