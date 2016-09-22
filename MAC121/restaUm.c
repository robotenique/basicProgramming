#include <stdio.h>
#include <stdlib.h>
#include "dataStructs.h"


#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

minINT ** criaTabuleiro(int m, int n);
int * getDadosTabuleiro (minINT **tab, int m, int n, posArray *posB, posArray *posP);
bool resolveRestaUm (minINT ** tab, int m, int n,int pecas,int buracos,posArray *posB,posArray *posP);
bool fazMovimento (minINT **tab , int m, int n, int pecas, posArray *posP, int j, minINT mov);
void desfazMovimento (minINT **tab, int m, int n, int pecas, posArray *posP, int j, minINT mov);
bool estaResolvido (posArray *posB, minINT **tab, int pecas, int buracos);
minINT podeMover(minINT **tab, int m, int n, pos p, minINT mov);
bool haPecas_buracos(posArray *posB,minINT **tab);
void debugPosicoes (posArray *pArr);
void imprimeTab (minINT **tab,int m, int n);

int main (int argc, char const *argv[]) {
    /*Declaração de variáveis */
    int m,n,i,j,pecas,buracos,aux = 0;
    int *dados;
    minINT ** tab;
    posArray *posB,*posP;

    /*Leitura de dados */
    scanf("%d%d",&m,&n);
    tab = criaTabuleiro (m,n);
    for (i = 0; i < m; i++)
        for (j = 0; j < n; j++)
        {
            scanf("%d", &aux);
            tab[i][j] = (minINT)aux;
        }
    /*Inicialização de dados */
    posB = criaPosArray(1);
    posP = criaPosArray(2);
    dados = getDadosTabuleiro(tab,m,n,posB,posP);
    pecas = dados[0];
    buracos = dados[1];
    free(dados);

    if(resolveRestaUm (tab,m,n,pecas,buracos,posB,posP))
        printf("TRUE\n");
    else{
        printf("NAOOOOOOOO\n");
        imprimeTab(tab,m,n);
    }

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

bool resolveRestaUm (minINT ** tab, int m, int n, int pecas,int buracos,posArray *posB,posArray *posP) {
    /* CUIDADO COM O FATO DOS posArray serem passados por referencia!! */
    int j;
    minINT mov;
    if(estaResolvido(posB,tab,pecas,buracos))   return true;
    for (j = 0; j < posP->i; j++)
        for (mov = 1; mov < 5 ; mov++)
            if (fazMovimento(tab,m,n,pecas,posP,j,mov)) {
                if(resolveRestaUm(tab,m,n,pecas,buracos,posB,posP)) return true;
                desfazMovimento(tab,m,n,pecas,posP,j,mov);
            }
    return false ;
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

int * getDadosTabuleiro (minINT **tab, int m, int n, posArray *posB, posArray *posP) {
    int i,j;
    pos nPos;
    int pecas = 0,buracos = 0;
    int * dados;
    dados = malloc(2 * sizeof(int));
    if (dados == NULL) {
        printf("Erro na alocação de memória, terminando programa...\n");
        exit(-1);
    }
    for (i = 0; i < m; i++)
        for (j = 0; j < n; j++)
            if (tab[i][j]==1) {
                pecas++;
                nPos.x = i;
                nPos.y = j;
                adicionaPos(posP,nPos);
            }
            else if (tab[i][j]==-1) {
                buracos++;
                nPos.x = i;
                nPos.y = j;
                adicionaPos(posB,nPos);

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

minINT podeMover(minINT **tab, int m, int n, pos p, minINT mov) {
    /*
     *    Movimentos possíves
     *           (2)
     *            ^
     *            |
     *            |
     *  (1) <-----X-----> (3)
     *            |
     *            |
     *            v
     *           (4)
     *
     *  Verificações feitas:
     *  Se o movimento não sairia do tabuleiro
     *  Se há uma peça intermediária para o movimento
     *  Se há um buraco para mover
     */
    switch (mov) {
        case 1:
            if(p.y - 2 < 0 || tab[p.x][p.y-1]!=1 || tab[p.x][p.y-2] != -1) return 0;
            break;
        case 2:
            if(p.x - 2 < 0 || tab[p.x-1][p.y]!=1 || tab[p.x-2][p.y] != -1) return 0;
            break;
        case 3:
            if(p.y + 2 > n-1 || tab[p.x][p.y+1]!=1 || tab[p.x][p.y+2] != -1) return 0;
            break;
        case 4:
            if(p.x + 2 > m-1 || tab[p.x+1][p.y]!=1 || tab[p.x+2][p.y] != -1) return 0;
            break;
    }
    return mov;
}

bool fazMovimento (minINT **tab , int m, int n, int pecas, posArray *posP, int j,minINT mov) {
    int movN;
    pos p = posP->p[j];
    if((movN = podeMover(tab,m,n,p,mov)))
        switch (movN) {
            case 1:
                tab[p.x][p.y-2] = 1;
                tab[p.x][p.y-1] = -1;
                tab[p.x][p.y] = -1;
                pecas--;
                posP->p[j].y = p.y - 2;
                return true;
            case 2:
                tab[p.x-2][p.y] = 1;
                tab[p.x-1][p.y] = -1;
                tab[p.x][p.y] = -1;
                pecas--;
                posP->p[j].x = p.x - 2;
                return true;
            case 3:
                tab[p.x][p.y+2] = 1;
                tab[p.x][p.y+1] = -1;
                tab[p.x][p.y] = -1;
                pecas--;
                posP->p[j].y = p.y + 2;
                return true;
            case 4:
                tab[p.x+2][p.y] = 1;
                tab[p.x+1][p.y] = -1;
                tab[p.x][p.y] = -1;
                pecas--;
                posP->p[j].x = p.x + 2;
                return true;
        }
    return false;
}

void desfazMovimento (minINT **tab, int m, int n, int pecas, posArray *posP, int j, minINT mov) {
    int movN;
    pos p = posP->p[j];
    switch (mov) {
        case 1:
            tab[p.x][p.y] = -1;
            tab[p.x][p.y+1] =1;
            tab[p.x][p.y+2] =1;
            pecas++;
            posP->p[j].y = p.y + 2;

        case 2:
        case 3:
        case 4:
    }
}

void debugPosicoes (posArray *pArr) {
    int i;
    for (i = 0; i < pArr->max ; printf("[%d , %d]\n",pArr->p[i].x,pArr->p[i].y ) , i++);
}

void imprimeTab (minINT **tab,int m, int n) {
    int i,j;
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++){
            if (tab[i][j]==0)
                printf("%s%3d",KWHT,tab[i][j]);
            else if (tab[i][j]==1)
                printf("%s%3d",KCYN,tab[i][j]);
            else
                printf("%s%3d",KMAG,tab[i][j]);
        }
        printf("\n");
    }
}
