#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
typedef enum { false, true } bool;
typedef struct {
      unsigned int x;
     unsigned  int y;
}par;
typedef char minINT;

minINT ** criaTabuleiro(int m, int n);
int * getDadosTabuleiro (minINT **tab, int m, int n);
void resolveRestaUm (minINT ** tab, int m, int n);

int main (int argc, char const *argv[]) {
    int m,n,i,j;
    int aux = 0;
    minINT ** tab;
    scanf("%d%d",&m,&n);
    tab = criaTabuleiro (m,n);
    for (i = 0; i < m; i++)
        for (j = 0; j < n; j++)
        {
            scanf("%d", &aux);
            tab[i][j] = (minINT)aux;
        }

    resolveRestaUm (tab,m,n);

    return 0;
}
minINT ** criaTabuleiro (int m, int n) {
    int i;
    minINT ** tab;
    tab = malloc(m * sizeof(minINT*));
    if (tab != NULL)
        for (i = 0; i < n; i++)
                tab[i] = malloc(n * sizeof(minINT));
    else {
        printf("Erro na alocação de memória, terminando programa...\n");
        exit(-1);
    }
    return tab;
}

void resolveRestaUm (minINT ** tab, int m, int n) {
/* Declaração de variáveis */
    stack mov;
    int pecas,buracos;
    int *dados;
    par * posB;
    dados = getDadosTabuleiro(tab,m,n);
    pecas = dados[0];
    buracos = dados[1];
    free(dados);
    while (!haPecas_buracos()) {
        /* code */
    }





    printf("pec %d\n",pecas );
    printf("bur %d\n",buracos );
return ;
}
/*
 * Funcao: getDadosTabuleiro
 * ----------------------------
 *   Retorna um vetor com a quantidade de peças e buracos , e armazena a posição
 *   de cada buraco.
 *   tab: matriz do tabuleiro
 *   m: número de linhas
 *   n: número de colunas
 *
 *   return: Vetor de três posições: [0] = nº de peças e [1] = número de buracos
 */

int * getDadosTabuleiro (minINT **tab, int m, int n, par * posB) {
    int i,j;
    int pecas = 0,buracos = 0;
    int * dados;
    dados = malloc(2 * sizeof(int));
    if (dados == NULL) {
        printf("Erro na alocação de memória, terminando programa...\n");
        exit(-1);
    }
    for (i = 0; i < m; i++)
        for (j = 0; j < n; j++)
            if (tab[i][j]==1)
                pecas++;
            else if (tab[i][j]==-1)
                buracos++;
    dados[0] = pecas;
    dados[1] = buracos;
    return dados;
}
