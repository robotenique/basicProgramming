#include <stdio.h>
#include <string.h>
#include <mcheck.h>
#include <ctype.h>
#include "arrayOps.h"
#include "buffer.h"
#include "tabelaSimbolo_VD.h"


typedef struct inputConfig {
    minINT stableType;
    bool orderByFreq;
} inputConfig;

void calculateFreqVD(FILE *input, Buffer *B, inputConfig conf);
char* getValidWord(char *word);
bool isValid (char c);
int max(int a, int b);

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
        conf.orderByFreq = true;
    else if(!strcmp(argv[3], "O"))
        conf.orderByFreq = false;
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
    int i, wide = 0, nwords = 0;
    st = stable_create();
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
                printf("word: %s\n",W->data );
                ir = stable_insert(st, W->data);
                if(ir.new) nwords++;
                ir.data->i = 1 + (!ir.new * ir.data->i);
            }
            buffer_reset(W);
        }
    }
}
bool isValid (char c) { return isalpha(c) || isdigit(c); }
int max(int a, int b) { return a > b ? a : b; }
