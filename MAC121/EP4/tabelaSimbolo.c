/*
 * @author: Juliano Garcia de Oliveira
 * nº usp = 9277086
 * MAC0121
 * 14/11/2016
 * Arquivo principal: Faz a leitura e chama as funções corretas.
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "arrayOps.h"
#include "frequenciaCalc.h"


/*
 * Função: main
 * --------------------------------------------------------
 * Lê os argumentos passados pela linha de comando, checa se houve erros
 * e chama as funções corretas para calcular a frequência.
 *
 * @args    argc: Quantidade de argumentos
 *          argv: Vetor com o conteúdo dos argumentos
 *
 * @return  retorno padrão do C
 */
int main(int argc, char const *argv[]) {
    FILE *input;
    inputConfig conf;
    /* Entrada e verificação de erros */
    if (argc != 4)
        die("Usage: ./ep4 <inputFile> <stableType> <sortingType>");
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



    /* Chama a função correta de acordo com a entrada */
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
