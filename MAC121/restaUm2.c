#include <stdio.h>
#include <stdlib.h>
#include "dataStructs.h"

typedef unsigned long int ulint;

minINT ** criaTabuleiro(int m, int n);
ulint * getDadosTabuleiro (minINT **tab, int m, int n, posArray *posB);
bool resolveRestaUm (minINT ** tab, int m, int n,ulint buracos,posArray *posB);
bool restUmBacktrack (minINT **tab, int m, int n, ulint nHoles, posArray *posB);
bool fazMovimento (minINT **tab , int m, int n, int j, minINT mov);
void desfazMovimento (minINT **tab, int m, int n,int j, minINT mov);
bool estaResolvido (posArray *posB, minINT **tab,ulint buracos);
minINT podeMover(minINT **tab, int m, int n, int j, minINT mov);
bool haPecas_buracos(posArray *posB,minINT **tab);
void printSolution (stack *mem, int n);
/*-------------DEBUG-------------*/
void debugPosicoes (posArray *pArr);
void imprimeTab (minINT **tab,int m, int n);
void lixou (minINT **tab, int l, int c, minINT mov, int m, int n);

ulint jCoord,pecas;
minINT c_mov;
unsigned  long cmp   = 0;

int main () {
    /*Declaração de variáveis */
    int m,n,i,k,aux = 0;
    ulint buracos = 0;
    ulint *dados;
    minINT ** tab;
    posArray *posB;

    /*Leitura de dados */
    scanf("%d%d",&m,&n);
    tab = criaTabuleiro (m,n);
    for (i = 0; i < m; i++)
        for (k = 0; k < n; k++)
        {
            scanf("%d", &aux);
            tab[i][k] = (minINT)aux;
        }
    /*Inicialização de dados */
    jCoord = 0;
    c_mov = 1;
    posB = criaPosArray(1);
    dados = getDadosTabuleiro(tab,m,n,posB);
    pecas = dados[0];
    buracos = dados[1];
    free(dados);
    
    if(!restUmBacktrack(tab,m,n,buracos,posB))
        printf("Impossivel\n");
    return 0;
}

minINT ** criaTabuleiro (int m, int n) {
    int i;
    minINT ** tab;
    tab = malloc(m * sizeof(minINT*));
    if (tab != NULL)
        for (i = 0; i < m; i++)
                tab[i] = malloc(n * sizeof(minINT));
    else {
        printf("Erro na alocação de memória, terminando programa...\n");
        exit(-1);
    }
    return tab;
}

bool restUmBacktrack (minINT **tab, int m, int n, ulint nHoles, posArray *posB)
{
    int j;
    bool ok;
    minINT mov;
    stack *mem;
    pMovData l_action;
    mem = newStack (pecas);
    while (true) {
         j = jCoord;
         /* Percorre todas as peças do tabuleiro.
          * Só sai do loop quando não houver mais movimentos possíveis!
          */
         while (j < m*n) {
             ok = false;
             if(tab[j/n][j%n]==1) {
                mov = c_mov;
                while (mov < 5 && !ok) {
                    if (fazMovimento(tab,m,n,j,mov))
                        ok = true;
                    mov++;
                }
                if (ok) {
                    push(mem,j,mov-1);
                    j = -1;
                }
                c_mov = 1;
             }
             j++;
         }
         if (estaResolvido(posB,tab,nHoles)) {
            printSolution(mem,n);
            return true;
        }
         if (isEmpty(*mem))
             return false;
         l_action = pop(mem);
         desfazMovimento(tab,m,n,l_action.jCoord,l_action.mov);
         c_mov = l_action.mov + 1;
         jCoord = l_action.jCoord;
    }
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

ulint * getDadosTabuleiro (minINT **tab, int m, int n, posArray *posB) {
    int i,j;
    pos nPos;
    ulint * dados;
    ulint buracos = 0;;
    pecas = 0;
    dados = malloc(2 * sizeof(ulint));
    if (dados == NULL)
        exit(-1);
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

bool estaResolvido (posArray *posB, minINT **tab, ulint buracos) {
    if (pecas == buracos)
        return haPecas_buracos(posB,tab);
    return false;
}

bool haPecas_buracos (posArray *posB, minINT **tab ) {
    int i;
    for(i = 0; i < posB->i ; i++)
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

bool fazMovimento (minINT **tab , int m, int n, int j,minINT mov)
{
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
    switch (mov) {
        case 1:
            tab[l][c] = 1;
            tab[l][c-1] = 1;
            tab[l][c-2] = -1;
            pecas++;
            break;
        case 2:
            tab[l-2][c] = -1;
            tab[l-1][c] = 1;
            tab[l][c] = 1;
            pecas++;
            break;
        case 3:
            tab[l][c] = 1;
            tab[l][c+1] =1;
            tab[l][c+2] =-1;
            pecas++;
            break;
        case 4:
            tab[l+2][c] = -1;
            tab[l+1][c] = 1;
            tab[l][c] = 1;
            pecas++;
            break;
    }
}

void printSolution (stack *mem, int n)
{
    int i,j;
    pos oldP,newP;

    for (i = 0; i < mem->top; i++) {
        j = mem->p_mov[i].jCoord;
        oldP.x = newP.x = j/n;
        oldP.y = newP.y = j%n;
        switch (mem->p_mov[i].mov) {
            case 1:
                newP.y = oldP.y - 2;
                break;
            case 2:
                newP.x = oldP.x - 2;
                break;
            case 3:
                newP.y = oldP.y + 2;
                break;
            case 4:
                newP.x = oldP.x + 2;
                break;
        }
        printf("%d:%d-%d:%d\n",oldP.x,oldP.y,newP.x,newP.y);
    }

}
