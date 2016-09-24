/*
 * @author: Juliano Garcia de Oliveira
 * nº usp = 9277086
 * MAC0121
 * 26/09/2016
 */
#include <stdio.h>
#include <stdlib.h>
#include "dataStructs.h"

/* Definição de tipos */
typedef unsigned long int ulint;

/* Protótipo de funções */
minINT ** newBoard (int m, int n);
ulint * getBoardData (minINT **tab, int m, int n, posArray *posH);
bool solvePeg (minINT **tab, int m, int n, ulint nHoles, posArray *posH);
bool doMove (minINT **tab , int m, int n, int j, minINT mov);
void undoMove (minINT **tab, int m, int n, int j, minINT mov);
bool isSolved (posArray *posH, minINT **tab, ulint nHoles);
minINT canMove (minINT **tab, int m, int n, int j, minINT mov);
bool allPegsAreHoles (posArray *posH, minINT **tab);
void printAndDestroy (stack *mem, int n, bool print);

ulint pegs;


int main () {
    /*Declaração de variáveis */
    int m, n, i, k, aux = 0;
    ulint nHoles = 0;
    ulint *data;
    minINT ** tab;
    posArray *posH;

    /*Leitura de dados */
    scanf ("%d%d", &m, &n);
    tab = newBoard (m, n);
    for (i = 0; i < m; i++)
        for (k = 0; k < n; k++) {
            scanf ("%d", &aux);
            tab[i][k] = (minINT) aux;
        }
    /*Inicialização de dados */
    posH = criaPosArray (1);
    data = getBoardData (tab,m,n,posH);
    pegs = data[0];
    nHoles = data[1];
    free (data);

    if (!solvePeg(tab,m,n,nHoles,posH))
        printf ("Impossivel\n");

    return 0;
}

minINT ** newBoard (int m, int n) {
    int i;
    minINT ** tab;

    tab = malloc (m*sizeof(minINT*));
    if (tab != NULL)
        for (i = 0; i < m; i++)
                tab[i] = malloc(n*sizeof(minINT));
    else
        exit(-1);

    return tab;
}

bool solvePeg (minINT **tab, int m, int n, ulint nHoles, posArray *posH) {
    int j;
    bool ok;
    ulint jCoord = 0;
    minINT mov, c_mov = 1;
    stack *mem;
    pMovData l_action;
    mem = newStack (pegs);

    while (true) {
         j = jCoord;
         while (j < m*n) {
             ok = false;
             if (tab[j/n][j%n] == 1) {
                mov = c_mov;
                while (mov < 5 && !ok) {
                    if (doMove(tab, m, n, j, mov))
                        ok = true;
                    mov++;
                }
                if (ok) {
                    push(mem, j, mov - 1);
                    j = -1;
                }
                c_mov = 1;
             }
             j++;
         }

         if (isSolved(posH, tab, nHoles)) {
            printAndDestroy (mem, n, true);
            return true;
        }
         if (isEmpty(*mem)) {
            printAndDestroy (mem, n, false);
             return false;
         }
         l_action = pop (mem);
         undoMove (tab, m, n, l_action.jCoord, l_action.mov);
         c_mov = l_action.mov + 1;
         jCoord = l_action.jCoord;
    }
}

/*
 * Funcao: getBoardData
 * ----------------------------
 *   Retorna um vetor com a quantidade de peças e nHoles , e armazena a posição
 *   de cada buraco.
 *   tab: matriz do tabuleiro
 *   m: número de linhas
 *   n: número de colunas
 *
 *   return: Vetor de três posições: [0] = nº de peças e [1] = número de nHoles
 */

ulint * getBoardData (minINT **tab, int m, int n, posArray *posH) {
    int i, j;
    pos nPos;
    ulint * data;
    ulint nHoles = 0;;
    pegs = 0;
    data = malloc(2*sizeof(ulint));

    if (data == NULL)
        exit(-1);
    for (i = 0; i < m; i++)
        for (j = 0; j < n; j++)
            if (tab[i][j] == 1)
                pegs++;
            else if (tab[i][j] == -1) {
                nHoles++;
                nPos.x = i;
                nPos.y = j;
                adicionaPos (posH, nPos);
            }

    data[0] = pegs;
    data[1] = nHoles;
    return data;
}

bool isSolved (posArray *posH, minINT **tab, ulint nHoles) {
    if (pegs == nHoles)
        return allPegsAreHoles (posH, tab);
    return false;
}

bool allPegsAreHoles (posArray *posH, minINT **tab ) {
    int i;

    for(i = 0; i < posH->i ; i++)
        if(tab[posH->p[i].x][posH->p[i].y] != 1)
            return false;
    return true;
}

minINT canMove(minINT **tab, int m, int n, int j, minINT mov) {
    int l = j/n, c = j%n;
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
            if(c - 2 < 0 || tab[l][c-1] != 1 || tab[l][c-2] != -1) return 0;
            break;
        case 2:
            if(l - 2 < 0 || tab[l-1][c] != 1 || tab[l-2][c] != -1) return 0;
            break;
        case 3:
            if(c + 2 > n-1 || tab[l][c+1] != 1 || tab[l][c+2] != -1) return 0;
            break;
        case 4:
            if(l + 2 > m-1 || tab[l+1][c] != 1 || tab[l+2][c] != -1) return 0;
            break;
    }
    return mov;
}

bool doMove (minINT **tab , int m, int n, int j,minINT mov) {
    minINT movN;
    int l, c;

    if((movN = canMove(tab, m, n, j, mov))) {
        l = j/n;
        c = j%n;
        switch (movN) {
            case 1:
                tab[l][c-2] = 1;
                tab[l][c-1] = -1;
                tab[l][c] = -1;
                pegs--;
                return true;
            case 2:
                tab[l-2][c] = 1;
                tab[l-1][c] = -1;
                tab[l][c] = -1;
                pegs--;
                return true;
            case 3:
                tab[l][c+2] = 1;
                tab[l][c+1] = -1;
                tab[l][c] = -1;
                pegs--;
                return true;
            case 4:
                tab[l+2][c] = 1;
                tab[l+1][c] = -1;
                tab[l][c] = -1;
                pegs--;
                return true;
        }
    }

    return false;
}

void undoMove (minINT **tab, int m, int n, int j, minINT mov) {
    int l = j/n, c = j%n;

    switch (mov) {
        case 1:
            tab[l][c] = 1;
            tab[l][c-1] = 1;
            tab[l][c-2] = -1;
            pegs++;
            break;
        case 2:
            tab[l-2][c] = -1;
            tab[l-1][c] = 1;
            tab[l][c] = 1;
            pegs++;
            break;
        case 3:
            tab[l][c] = 1;
            tab[l][c+1] = 1;
            tab[l][c+2] = -1;
            pegs++;
            break;
        case 4:
            tab[l+2][c] = -1;
            tab[l+1][c] = 1;
            tab[l][c] = 1;
            pegs++;
            break;
    }
}

void printSolution (stack *mem, int n) {
    int i,j;
    pos oldP,newP;

    for (i = 0; i < mem->top && print; i++) {
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
        printf("%d:%d-%d:%d\n", oldP.x, oldP.y, newP.x, newP.y);
    }
}
