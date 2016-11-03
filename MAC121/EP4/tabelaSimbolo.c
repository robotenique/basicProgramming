#include <stdio.h>
#include <string.h>
#include <mcheck.h>
#include <stdlib.h>
#include "arrayOps.h"
#include "buffer.h"
#include "tabelaSimbolo_VD.h"
#include "tabelaSimbolo_VO.h"
#include "tabelaSimbolo_LD.h"
#include "tabelaSimbolo_LO.h"
#include "tabelaSimbolo_AB.h"

/* Para debug em gdb:
 gcc -Wall -ansi -pedantic -pg -g -o a.out tabelaSimbolo.c buffer.c tabelaSimbolo_VO.c tabelaSimbolo_VD.c tabelaSimbolo_LD.c tabelaSimbolo_LO.c tabelaSimbolo_AB.c arrayOps.c
*/
typedef struct inputConfig {
    minINT stableType;
    bool orderByAlpha;
} inputConfig;




void calculateFreqVD (FILE *input, inputConfig conf);
void calculateFreqVO (FILE *input, inputConfig conf);
void calculateFreqLD (FILE *input, inputConfig conf);
void calculateFreqLO (FILE *input, inputConfig conf);
void calculateFreqAB (FILE *input, inputConfig conf);
void printFreqVD (inputConfig conf, SymbolTableVD st, int wide, int n);
void printFreqVO (inputConfig conf, SymbolTableVO st, int wide, int n);
void printFreqLD (inputConfig conf, SymbolTableLD st, int wide, int n);
void printFreqLO (inputConfig conf, SymbolTableLO st, int wide, int n);
void printFreqAB (inputConfig conf, SymbolTableAB st, int wide, int n);
void copyValue_BST (const char *key, EntryData *data, word_BST *arr);
int  copyValue (const char *key, EntryData *data, word *arr, int i);

int main(int argc, char const *argv[]) {
    FILE *input;
    inputConfig conf;
    /* TODO: UNCOMMENT WHEN NEEDED! */
    /* Entrada e verificação de erros
    if (argc != 4)
        die("Not Usage: ./ep4 <inputFile> <stableType> <sortingType>");
    if(!strcmp(argv[2],"VD"))
        conf.stableType = 1;
    else if (!strcmp(argv[2],"VO"))
        conf.stableType = 2;
    else if (!strcmp(argv[2],"LD"))
        conf.stableType = 3;
    else if (!strcmp(argv[2],"LO"))
        conf.stableType = 4;
    else if (!strcmp(argv[2],"AB"))
        conf.stableType = 5;
    else
        die("Error: Provide a correct Symbol Table type!");
    if(!strcmp(argv[3], "A"))
        conf.orderByAlpha = true;
    else if(!strcmp(argv[3], "O"))
        conf.orderByAlpha = false;
    else
        die("Error: Provide a correct sorting method!");
    input = fopen(argv[1], "r");
    if (input == NULL)
       die("Error opening file, aborting...");
    */
    input = fopen("in", "r");
    conf.stableType = 1;
    conf.orderByAlpha = true;

    switch (conf.stableType) {
        case 1:
            calculateFreqVD(input, conf);
            break;
        case 2:
            calculateFreqVO(input, conf);
            break;
        case 3:
            calculateFreqLD(input, conf);
            break;
        case 4:
            calculateFreqLO(input, conf);
            break;
        case 5:
            calculateFreqAB(input, conf);
            break;
    }
    fclose(input);
    return 0;
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
                ir = insertST_VO(st, W->data); /* Consider Polymorphism... */
                if(ir.new) nElements++;
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

void printFreqVO(inputConfig conf, SymbolTableVO st, int wide, int n) {
    int i, nSpaces;
    word* wArr = calloc(n, sizeof(word));
    if (wArr == NULL) die("Error in memory allocation!");
    applyST_VO(st, &copyValue, wArr);
    if(!conf.orderByAlpha)
        qsort(wArr, n, sizeof(word), compareFreq);
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
void copyValue_BST (const char *key, EntryData *data, word_BST *arr) {
    arr->wArr[arr->i].p = estrdup(key);
    arr->wArr[arr->i++].freq = data->i;
}
int copyValue(const char *key, EntryData *data, word *arr, int i) {
    arr[i].p = estrdup(key);
    arr[i].freq = data->i;
    return 1;
}
