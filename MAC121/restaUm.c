#include <stdio.h>
#include <stdlib.h>
#include "dataStructs.h"
#include <unistd.h>


#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"
#define KYEL  "\x1B[33m"
#define KRED  "\x1B[31m"
#define KBLU  "\x1B[34m"



minINT ** criaTabuleiro(int m, int n);
int * getDadosTabuleiro (minINT **tab, int m, int n, posArray *posB);
bool resolveRestaUm (minINT ** tab, int m, int n,int buracos,posArray *posB);
bool fazMovimento (minINT **tab , int m, int n, int j, minINT mov);
void desfazMovimento (minINT **tab, int m, int n,int j, minINT mov);
bool estaResolvido (posArray *posB, minINT **tab,int buracos);
minINT podeMover(minINT **tab, int m, int n, int j, minINT mov);
bool haPecas_buracos(posArray *posB,minINT **tab);
/*-------------DEBUG-------------*/
void debugPosicoes (posArray *pArr);
void imprimeTab (minINT **tab,int m, int n);
void lixou (minINT **tab, int l, int c, minINT mov, int m, int n);


int pecas = 0;

int main (int argc, char const *argv[]) {
    /*Declaração de variáveis */
    int m,n,i,j,buracos,aux = 0;
    int *dados;
    minINT ** tab;
    posArray *posB;

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
    dados = getDadosTabuleiro(tab,m,n,posB);
    pecas = dados[0];
    buracos = dados[1];
    free(dados);

    if(resolveRestaUm (tab,m,n,buracos,posB))
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

bool resolveRestaUm (minINT ** tab, int m, int n,int buracos,posArray *posB) {
    /* CUIDADO COM O FATO DOS posArray serem passados por referencia!! */
    int j;
    minINT mov;
    /*sleep(1);*/
    if(estaResolvido(posB,tab,buracos)){imprimeTab(tab,m,n); return true;}
    else if (pecas <= n) return false;
    for (j = 0; j < m*n; j++){
    /*printf("[%d][%d]\n",j,n); sleep(1);*/
        if(tab[j/n][j%n]==1){
            for (mov = 1; mov < 5 ; mov++)
                if (fazMovimento(tab,m,n,j,mov)) {
                    if(resolveRestaUm(tab,m,n,buracos,posB)) return true;
                    desfazMovimento(tab,m,n,j,mov);
                }}}
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

int * getDadosTabuleiro (minINT **tab, int m, int n, posArray *posB) {
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
            if (tab[i][j]==1)
                pecas++;
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

bool estaResolvido (posArray *posB, minINT **tab, int buracos) {
    if (pecas == buracos){
        printf("iS = %d\n",pecas );
        return haPecas_buracos(posB,tab);
    }
    return false;
}

bool haPecas_buracos (posArray *posB, minINT **tab ) {
    int i;
    for(i = 0; i < posB->max ; i++)
        if(tab[posB->p[i].x][posB->p[i].y]!=1)
            return false;
    return true;
}

minINT podeMover(minINT **tab, int m, int n, int j, minINT mov) {
    int l = j/n, c = j%n;
    if(l > 6)printf("(pM) L = %d ",l );
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
            if(c - 2 < 0 || tab[l][c-1]!=1 || tab[l][c-2] != -1) return 0;
            break;
        case 2:
            if(l - 2 < 0 || tab[l-1][c]!=1 || tab[l-2][c] != -1) return 0;
            break;
        case 3:
            if(c + 2 > n-1 || tab[l][c+1]!=1 || tab[l][c+2] != -1) return 0;
            break;
        case 4:
            if(l + 2 > m-1 || tab[l+1][c]!=1 || tab[l+2][c] != -1) return 0;
            break;
    }
    return mov;
}

bool fazMovimento (minINT **tab , int m, int n, int j,minINT mov) {
    minINT movN;
    int l=0,c=0;
    if((movN = podeMover(tab,m,n,j,mov))) {
        l = j/n;
        c = j%n;
        switch (movN) {
            case 1:
                tab[l][c-2] = 1;
                tab[l][c-1] = -1;
                tab[l][c] = -1;
                pecas--;
                return true;
            case 2:
                tab[l-2][c] = 1;
                tab[l-1][c] = -1;
                tab[l][c] = -1;
                pecas--;
                return true;
            case 3:
                tab[l][c+2] = 1;
                tab[l][c+1] = -1;
                tab[l][c] = -1;
                pecas--;
                return true;
            case 4:
                tab[l+2][c] = 1;
                tab[l+1][c] = -1;
                tab[l][c] = -1;
                pecas--;
                return true;
        }

    }
    return false;
}

void desfazMovimento (minINT **tab, int m, int n,int j, minINT mov) {
    int l = j/n, c = j%n;
    printf("%s                           ANTES\n",KYEL );
    imprimeTab(tab,m,n);
    switch (mov) {
        case 1:
            tab[l][c] = 1;
            tab[l][c-1] = 1;
            tab[l][c-2] = -1;
            pecas++;
            lixou(tab,l,c,mov,m,n);
            break;
        case 2:
            tab[l-2][c] = -1;
            tab[l-1][c] = 1;
            tab[l][c] = 1;
            pecas++;
            lixou(tab,l,c,mov,m,n);
            break;
        case 3:
            tab[l][c] = -1;
            tab[l][c-1] =1;
            tab[l][c-2] =1;
            pecas++;
            lixou(tab,l,c,mov,m,n);
            break;
        case 4:
            tab[l+2][c] = -1;
            tab[l+1][c] = 1;
            tab[l][c] = 1;
            pecas++;
            lixou(tab,l,c,mov,m,n);
            break;
    }
    printf("%s                           DEPOIS\n",KBLU );
    printf("                    |%s tab[%d][%d], mov = %d|\n",KBLU,l,c,mov);
    imprimeTab(tab,m,n);
}

void debugPosicoes (posArray *pArr) {
    int i;
    for (i = 0; i < pArr->max ; printf("[%d , %d]\n",pArr->p[i].x,pArr->p[i].y ) , i++);
}

void imprimeTab (minINT **tab,int m, int n) {
    int i,j;
    printf("%s ============================================================\n",KRED);

    for (i = 0; i < m; i++) {
        printf("%s |                   ",KRED);
        for (j = 0; j < n; j++){
            if (tab[i][j]==0)
                printf("%s-  ",KWHT);
            else if (tab[i][j]==1)
                printf("%sO  ",KCYN);
            else
                printf("%sx  ",KMAG);
        }
        printf("%s                  |\n",KRED);
    }
    printf("%s ============================================================\n",KRED);
}

void lixou (minINT **tab, int l, int c, minINT mov, int m, int n) {
    if (tab[6][0]!=0 || tab[6][1]!=0 || tab[5][0]!=0 || tab[5][1]!=0) {
        printf("%s>>>>>>>>>> LIXOU!! DbLog = {tab[%d][%d], mov = %d} <<<<<<<<<<<<\n",KBLU,l,c,mov);
        imprimeTab(tab,m,n);
        exit(-1);
    }
}
