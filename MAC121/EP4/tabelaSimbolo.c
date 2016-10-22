#include <stdio.h>
#include <string.h>
#include <mcheck.h>
#include <ctype.h>
#include <stdlib.h>
#include "arrayOps.h"
#include "buffer.h"
#include "tabelaSimbolo_VD.h"


typedef struct inputConfig {
    minINT stableType;
    bool orderByAlpha;
} inputConfig;


void calculateFreqVD(FILE *input, Buffer *B, inputConfig conf);
void printFreqVD(inputConfig conf, SymbolTableVD st, int wide, int n);
int visitVD (const char *key, EntryData *data, word *arr, int i);

char* getValidWord(char *word);
bool isValid (char c);
int max(int a, int b);
int compareAlphabet (const void * a, const void * b);
int compareFreq (const void * a, const void * b);

int main(int argc, char const *argv[]) {
    FILE *input;
    Buffer *B;
    inputConfig conf;
    B = buffer_create();
    mcheck(0);
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
            calculateFreqVD(input, B, conf);
            break;
        case 2:

            break;
        case 3:

            break;
        case 4:

            break;
        case 5:

            break;
    }
    return 0;
}


void calculateFreqVD(FILE *input, Buffer *B, inputConfig conf) {
    SymbolTableVD st;
    Buffer *W;
    InsertionResult ir;
    int i, wide = 0, nElements = 0;
    st = stable_createVD();
    W = buffer_create();
    while (read_line(input,B)) {
        buffer_push_back(B,0);
        i = 0;
        while (B->data[i] != 0) {
            for (;isdigit(B->data[i]) || !isalpha(B->data[i]); i++);
            while (isValid(B->data[i]) && B->data[i] != 0 && i < (B -> i))
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
    printFreqVD(conf, st, wide, nElements);
}

void printFreqVD(inputConfig conf, SymbolTableVD st, int wide, int n) {
    int i, nSpaces;
    word* wArr = emalloc(sizeof(word) * n);
    stable_visitVD(st, &visitVD, wArr);
    if(conf.orderByAlpha)
        qsort(wArr, n, sizeof(word), compareAlphabet);
    else
        qsort(wArr, n, sizeof(word), compareFreq);
    /* Print the words and their frequency */
    for (i = 0; i < n; i++) {
        nSpaces = (int) (wide - strlen(wArr[i].p));
        printf("%s %*d\n", wArr[i].p, nSpaces, wArr[i].freq);
    }
}

int visitVD (const char *key, EntryData *data, word *arr, int i) {
    arr[i].p = estrdup(key);
    arr[i].freq = data->i;
    return 1;
}
bool isValid(char c)  { return isalpha(c) || isdigit(c); }
int max(int a, int b) { return a > b ? a : b; }
int compareAlphabet (const void * a, const void * b) {
  return strcmp(((word *)a)->p, ((word *)b)->p);
}
int compareFreq (const void * a, const void * b) {
    int freqA = ((word *)a)->freq;
    int freqB = ((word *)b)->freq;
    if(freqA < freqB)
        return 1;
    else if(freqA > freqB)
        return -1;
    return 0;
}
