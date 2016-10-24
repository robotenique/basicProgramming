#include <stdio.h>
#include <string.h>
#include <mcheck.h>
#include <ctype.h>
#include <stdlib.h>
#include "arrayOps.h"
#include "buffer.h"
#include "tabelaSimbolo_VD.h"
#include "tabelaSimbolo_VO.h"


typedef struct inputConfig {
    minINT stableType;
    bool orderByAlpha;
} inputConfig;


void calculateFreqVD(FILE *input, inputConfig conf);
void printFreqVD(inputConfig conf, SymbolTableVD st, int wide, int n);
void calculateFreqVO(FILE *input, inputConfig conf);
int visitVD (const char *key, EntryData *data, word *arr, int i);

bool isValid (char c);
bool isNotAlpha(char c);
int max(int a, int b);

int main(int argc, char const *argv[]) {
    FILE *input;
    inputConfig conf;
    /* Entrada e verificação de erros */
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

    switch (conf.stableType) {
        case 1:
            calculateFreqVD(input, conf);
            break;
        case 2:
            calculateFreqVO(input, conf);
            break;
        case 3:

            break;
        case 4:

            break;
        case 5:

            break;
    }
    fclose(input);
    return 0;
}

void calculateFreqVO(FILE *input, inputConfig conf) {
    return;
}

void calculateFreqVD(FILE *input, inputConfig conf) {
    SymbolTableVD st;
    Buffer *B;
    Buffer *W;
    InsertionResult ir;
    int i, wide = 0, nElements = 0;
    st = stable_createVD();
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
                ir = stable_insertVD(st, W->data);
                if(ir.new) nElements++;
                ir.data->i = 1 + (!ir.new * ir.data->i);
            }
            buffer_reset(W);
        }
    }
    buffer_destroy(B);
    buffer_destroy(W);
    printFreqVD(conf, st, wide, nElements);
    stable_destroyVD(st);
}

void printFreqVD(inputConfig conf, SymbolTableVD st, int wide, int n) {
    int i, nSpaces;
    word* wArr = calloc(n, sizeof(word));
    if (wArr == NULL) die("Error in memory allocation!");
    stable_visitVD(st, &visitVD, wArr);
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

int visitVD (const char *key, EntryData *data, word *arr, int i) {
    arr[i].p = estrdup(key);
    arr[i].freq = data->i;
    return 1;
}

/* Funções auxiliares */
bool isValid(char c)  { return isalpha(c) || isdigit(c); }
bool isNotAlpha(char c) {
    return isdigit(c) || !isalpha(c);
}
