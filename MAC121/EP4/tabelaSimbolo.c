#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "arrayOps.h"
#include "frequenciaCalc.h"


/* Para debug em gdb:
 gcc -Wall -ansi -pedantic -pg -g -o a.out tabelaSimbolo.c buffer.c tabelaSimbolo_VO.c tabelaSimbolo_VD.c tabelaSimbolo_LD.c tabelaSimbolo_LO.c tabelaSimbolo_AB.c arrayOps.c
@TODO: CHECAR STRCMP em tabelaLO
*/

void copyValue_BST (const char *key, EntryData *data, word_BST *arr);

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

    /* ~~OLOCO~~
     * VD =  3.57s
     * VO =  0.50s
     * LD = 33.38s
     * LO = 54.73s
     * AB = 0.34s
     */

    input = fopen("in", "r");
    conf.stableType = 4;
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