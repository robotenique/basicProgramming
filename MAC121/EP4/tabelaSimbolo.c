#include <stdio.h>
#include <string.h>
#include <mcheck.h>
#include <stdlib.h>
#include "arrayOps.h"
#include "buffer.h"
#include "tabelaSimbolo_VD.h"
#include "tabelaSimbolo_VO.h"
#include "tabelaSimbolo_LD.h"

/* Para debug em gdb:
 gcc -Wall -ansi -pedantic -O2 -g -o a.out tabelaSimbolo.c buffer.c tabelaSimbolo_VO.c tabelaSimbolo_VD.c arrayOps.c
*/
typedef struct inputConfig {
    minINT stableType;
    bool orderByAlpha;
} inputConfig;



void calculateFreqVD(FILE *input, inputConfig conf);
void calculateFreqVO(FILE *input, inputConfig conf);
void calculateFreqLD(FILE *input, inputConfig conf);
void printFreqVD(inputConfig conf, SymbolTableVD st, int wide, int n);
void printFreqVO(inputConfig conf, SymbolTableVO st, int wide, int n);
void printFreqLD(inputConfig conf, SymbolTableVO st, int wide, int n);
int copyValue (const char *key, EntryData *data, word *arr, int i);

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
    conf.stableType = 3;
    conf.orderByAlpha = false;

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

            break;
        case 5:

            break;
    }
    fclose(input);
    return 0;
}
void calculateFreqLD(FILE *input, inputConfig conf) {
    SymbolTableLD st;
    Buffer *B;
    Buffer *W;
    InsertionResult ir;
    int i, wide = 0, nElements = 0;
    st = createST_LD(!conf.orderByAlpha);
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
void printFreqLD(inputConfig conf, SymbolTableVO st, int wide, int n) {
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

int copyValue(const char *key, EntryData *data, word *arr, int i) {
    arr[i].p = estrdup(key);
    arr[i].freq = data->i;
    return 1;
}
