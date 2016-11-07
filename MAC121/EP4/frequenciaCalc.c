/*
 * @author: Juliano Garcia de Oliveira
 * nº usp = 9277086
 * MAC0121
 * 14/11/2016
 * Arquivo com as funções de cálculo e impressão das frequências.
 * Maiores detalhes sobre as funções no arquivo header.
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "arrayOps.h"
#include "buffer.h"
#include "tabelaSimbolo_VD.h"
#include "tabelaSimbolo_VO.h"
#include "tabelaSimbolo_LD.h"
#include "tabelaSimbolo_LO.h"
#include "tabelaSimbolo_AB.h"

/* -------------------------Funções de impressão--------------------------
 * printFreqVO;
 * printFreqVD;
 * printFreqLD;
 * printFreqLO;
 * printFreqAB.
 * Todas estas funções copiam a tabela de símbolos para um vetor,
 * ordenam este vetor se for necessário, e em seguida imprimem os pares
 * 'palavra' - 'frequencia'.
 */
void printFreqVO(inputConfig conf, SymbolTableVO st, int wide, int n) {
    int i, nSpaces;
    word* wArr = calloc(n, sizeof(word));
    if (wArr == NULL) die("Error in memory allocation!");
    /* Copia a tabela de símbolos para um vetor */
    applyST_VO(st, &copyValue, wArr);
    /* Caso necessaŕio, ordena o  vetor */
    if(!conf.orderByAlpha)
        qsort(wArr, n, sizeof(word), compareFreq);
    /* Impressão */
    for (i = 0; i < n; i++) {
        nSpaces = (int) (wide - strlen(wArr[i].p));
        printf("%s %*d\n", wArr[i].p, nSpaces, wArr[i].freq);
        free(wArr[i].p);
    }
    free(wArr);
}

void printFreqVD(inputConfig conf, SymbolTableVD st, int wide, int n) {
    int i, nSpaces;
    word* wArr = calloc(n, sizeof(word));
    if (wArr == NULL) die("Error in memory allocation!");
    applyST_VD(st, &copyValue, wArr);
    if(conf.orderByAlpha)
        qsort(wArr, n, sizeof(word), compareAlphabet);
    else
        qsort(wArr, n, sizeof(word), compareFreq);
    /* Print the words and their frequency */
    for (i = 0; i < n; i++) {
        nSpaces = (int) (wide - strlen(wArr[i].p));
        printf("%s %*d\n", wArr[i].p, nSpaces, wArr[i].freq);
        free(wArr[i].p);
    }
    free(wArr);
}

void printFreqLD(inputConfig conf, SymbolTableLD st, int wide, int n) {
    int i, nSpaces;
    word* wArr = calloc(n, sizeof(word));
    if (wArr == NULL) die("Error in memory allocation!");
    applyST_LD(st, &copyValue, wArr);
    if(conf.orderByAlpha)
        qsort(wArr, n, sizeof(word), compareAlphabet);
    else
        qsort(wArr, n, sizeof(word), compareFreq);
    for (i = 0; i < n; i++) {
        nSpaces = (int) (wide - strlen(wArr[i].p));
        printf("%s %*d\n", wArr[i].p, nSpaces, wArr[i].freq);
        free(wArr[i].p);
    }
    free(wArr);
}

void printFreqLO(inputConfig conf, SymbolTableLO st, int wide, int n) {
    int i, nSpaces;
    word* wArr = calloc(n, sizeof(word));
    if (wArr == NULL) die("Error in memory allocation!");
    applyST_LO(st, &copyValue, wArr);
    if(!conf.orderByAlpha)
        qsort(wArr, n, sizeof(word), compareFreq);
    for (i = 0; i < n && wArr[i].p != NULL; i++) {
        nSpaces = (int) (wide - strlen(wArr[i].p));
        printf("%s %*d\n", wArr[i].p, nSpaces, wArr[i].freq);
        free(wArr[i].p);
    }
    free(wArr);
}

void printFreqAB(inputConfig conf, SymbolTableAB st, int wide, int n) {
    int i, nSpaces;
    word_BST wBST;
    wBST.i = 0;
    wBST.wArr = calloc(n, sizeof(word));
    if (wBST.wArr == NULL) die("Error in memory allocation!");
    applyST_AB(st, &copyValue_BST, &(wBST));
    if(!conf.orderByAlpha)
        qsort(wBST.wArr, n, sizeof(word), compareFreq);
    for (i = 0; i < n && wBST.wArr[i].p != NULL; i++) {
        nSpaces = (int) (wide - strlen(wBST.wArr[i].p));
        printf("%s %*d\n", wBST.wArr[i].p, nSpaces, wBST.wArr[i].freq);
        free(wBST.wArr[i].p);
    }
    free(wBST.wArr);
}

void calculateFreqVO(FILE *input, inputConfig conf) {
    SymbolTableVD st;
    Buffer *B;
    Buffer *W;
    InsertionResult ir;
    int i, wide = 0, nElements = 0;
    st = createST_VO(!conf.orderByAlpha);
    B = buffer_create();
    W = buffer_create();
    while (read_line(input,B)) {
        /* Adiciona um '0' para marcar o final da string */
        buffer_push_back(B,0);
        i = 0;
        while (i < B->i && B->data[i] != 0) {
            /* Preenche o buffer W com a palavra */
            for (; i < B->i && isNotAlpha(B->data[i]); i++);
            while (i < (B -> i) &&  B->data[i] != 0 && isValid(B->data[i]))
                buffer_push_back(W,B->data[i++]);
            i++;
            if(W->i != 0) {
                buffer_push_back(W,0);
                wide = max(wide, W->i);
                buffer_lower(W);
                /* Insere a palavra na tabela de símbolos */
                ir = insertST_VO(st, W->data);
                if(ir.new) nElements++;
                /* Se a palavra for nova, a frequência vale 1,
                 * senão é somado 1 à frequência.
                 */
                ir.data->i = 1 + (!ir.new * ir.data->i);
            }
            buffer_reset(W);
        }
    }
    buffer_destroy(B);
    buffer_destroy(W);
    printFreqVO(conf, st, wide, nElements);
    destroyST_VO(st);
}

void calculateFreqVD(FILE *input, inputConfig conf) {
    SymbolTableVD st;
    Buffer *B;
    Buffer *W;
    InsertionResult ir;
    int i, wide = 0, nElements = 0;
    st = createST_VD();
    B = buffer_create();
    W = buffer_create();
    while (read_line(input,B)) {
        buffer_push_back(B,0);
        i = 0;
        while (i < B->i && B->data[i] != 0) {
            for (; i < B->i && isNotAlpha(B->data[i]); i++);
            while (i < (B -> i) &&  B->data[i] != 0 && isValid(B->data[i]))
                buffer_push_back(W,B->data[i++]);
            i++;
            if(W->i != 0) {
                buffer_push_back(W,0);
                wide = max(wide, W->i);
                buffer_lower(W);
                ir = insertST_VD(st, W->data);
                if(ir.new) nElements++;
                ir.data->i = 1 + (!ir.new * ir.data->i);
            }
            buffer_reset(W);
        }
    }
    buffer_destroy(B);
    buffer_destroy(W);
    printFreqVD(conf, st, wide, nElements);
    destroyST_VD(st);
}

void calculateFreqLD(FILE *input, inputConfig conf) {
    SymbolTableLD st;
    Buffer *B;
    Buffer *W;
    InsertionResult ir;
    int i, wide = 0, nElements = 0;
    st = createST_LD();
    B = buffer_create();
    W = buffer_create();
    while (read_line(input,B)) {
        buffer_push_back(B,0);
        i = 0;
        while (i < B->i && B->data[i] != 0) {
            for (; i < B->i && isNotAlpha(B->data[i]); i++);
            while (i < (B -> i) &&  B->data[i] != 0 && isValid(B->data[i]))
                buffer_push_back(W,B->data[i++]);
            i++;
            if(W->i != 0) {
                buffer_push_back(W,0);
                wide = max(wide, W->i);
                buffer_lower(W);
                ir = insertST_LD(st, W->data);
                if(ir.new) nElements++;
                ir.data->i = 1 + (!ir.new * ir.data->i);
            }
            buffer_reset(W);
        }
    }
    buffer_destroy(B);
    buffer_destroy(W);
    printFreqLD(conf, st, wide, nElements);
    destroyST_LD(st);
}

void calculateFreqLO(FILE *input, inputConfig conf) {
    SymbolTableLO st;
    Buffer *B;
    Buffer *W;
    InsertionResult ir;
    int i, wide = 0, nElements = 0;
    st = createST_LO();
    B = buffer_create();
    W = buffer_create();
    while (read_line(input,B)) {
        buffer_push_back(B,0);
        i = 0;
        while (i < B->i && B->data[i] != 0) {
            for (; i < B->i && isNotAlpha(B->data[i]); i++);
            while (i < (B -> i) &&  B->data[i] != 0 && isValid(B->data[i]))
                buffer_push_back(W,B->data[i++]);
            i++;
            if(W->i != 0) {
                buffer_push_back(W,0);
                wide = max(wide, W->i);
                buffer_lower(W);
                ir = insertST_LO(st, W->data);
                if(ir.new != 0) nElements++;
                ir.data->i = 1 + (!ir.new * ir.data->i);

            }
            buffer_reset(W);
        }
    }
    buffer_destroy(B);
    buffer_destroy(W);
    printFreqLO(conf, st, wide, nElements);
    destroyST_LO(st);
}

void calculateFreqAB(FILE *input, inputConfig conf) {
    SymbolTableAB st;
    Buffer *B;
    Buffer *W;
    InsertionResult ir;
    int i, wide = 0, nElements = 0;
    st = createST_AB();
    B = buffer_create();
    W = buffer_create();
    while (read_line(input,B)) {
        buffer_push_back(B,0);
        i = 0;
        while (i < B->i && B->data[i] != 0) {
            for (; i < B->i && isNotAlpha(B->data[i]); i++);
            while (i < (B -> i) &&  B->data[i] != 0 && isValid(B->data[i]))
                buffer_push_back(W,B->data[i++]);
            i++;
            if(W->i != 0) {
                buffer_push_back(W,0);
                wide = max(wide, W->i);
                buffer_lower(W);
                ir = insertST_AB(st, W->data);
                if(ir.new != 0) nElements++;
                ir.data->i = 1 + (!ir.new * ir.data->i);
            }
            buffer_reset(W);
        }
    }
    buffer_destroy(B);
    buffer_destroy(W);
    printFreqAB(conf, st, wide, nElements);
    destroyST_AB(st);
}
