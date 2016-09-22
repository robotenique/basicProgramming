#include <stdio.h>
#include <stdlib.h>
#include "dataStructs.h"


minINT ** criaTabuleiro(int m, int n);
int * getDadosTabuleiro (minINT **tab, int m, int n, posArray *posB);
void resolveRestaUm (minINT ** tab, int m, int n);
bool estaResolvido (posArray *posB, minINT **tab, int pecas, int buracos);
bool haPecas_buracos(posArray *posB,minINT **tab);

void debugBuracos (posArray *posB);

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
    posArray * posB;
    posB = criaPosArray(1);
    dados = getDadosTabuleiro(tab,m,n,posB);
    pecas = dados[0];
    buracos = dados[1];
    free(dados);
    while (!estaResolvido(posB,tab,pecas,buracos)) {
        break;
    }




    debugBuracos(posB);
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

int * getDadosTabuleiro (minINT **tab, int m, int n, posArray *posB) {
    int i,j;
    pos bPos;
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
            else if (tab[i][j]==-1) {
                buracos++;
                bPos.x = i;
                bPos.y = j;
                adicionaPos(posB,bPos);

            }
    dados[0] = pecas;
    dados[1] = buracos;
    return dados;
}

bool estaResolvido (posArray *posB, minINT **tab, int pecas, int buracos) {
    if (pecas == buracos)
        return haPecas_buracos(posB,tab);
    return false;
}

bool haPecas_buracos (posArray *posB, minINT **tab ) {
    int i;
    for(i = 0; i < posB->max ; i++)
        if(tab[posB->p[i].x][posB->p[i].y]!=1)
            return false;
    return true;
}

void debugBuracos (posArray *posB) {
    int i;
    for (i = 0; i < posB->max ; printf("[%d , %d]\n",posB->p[i].x,posB->p[i].y ) , i++);
}
