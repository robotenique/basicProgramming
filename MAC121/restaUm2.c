/*
 * @author: Juliano Garcia de Oliveira
 * nº usp = 9277086
 * MAC0121
 * 26/09/2016
 */

#include <stdio.h>
#include <stdlib.h>
#include "dataStructs.h"

/* Protótipo de funções */
minINT ** newBoard (int m, int n);
ulint * getBoardData (minINT **tab, int m, int n, posArray *posH);
bool solvePeg (minINT **tab, int m, int n, ulint nHoles, posArray *posH);
bool doMove (minINT **tab , int m, int n, int j, minINT mov);
void undoMove (minINT **tab, int m, int n, int j, minINT mov);
bool isSolved (posArray *posH, minINT **tab, ulint nHoles);
minINT canMove (minINT **tab, int m, int n, int j, minINT mov);
bool allPegsAreHoles (posArray *posH, minINT **tab);
void printSolution (stack *mem, int n);
void destroy(minINT **tab, int m, posArray *posH, stack *mem);

ulint pegs;

/*
 * Função: main
 * --------------------------------------------------------
 *   Lê os dados da entrada padrão, inicializa variáveis e chama a função para
 *   tentar resolver o tabuleiro lido.
 * @args
 *
 * @return retorno padrão da linguagem C.
 */
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
    posH = newPosArray (1);
    data = getBoardData (tab,m,n,posH);
    pegs = data[0];
    nHoles = data[1];
    free (data);

    if (!solvePeg(tab,m,n,nHoles,posH))
        printf ("Impossivel\n");

    return 0;
}

/*
 * Função: newBoard
 * --------------------------------------------------------
 *   Aloca uma matriz  m*n para o tabuleiro do jogo e a retorna.
 * @args  m: número de linhas
 *        n: número de colunas
 *
 * @return matriz do tabuleiro, de tipo minINT
 */
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

/*
 * Função: solvePeg
 * --------------------------------------------------------
 *   Resolve o jogo Resta Um (peg solitaire) , usando o algoritmo de backtrack.
 *
 * @args  tab: matriz do tabuleiro
 *        m: número de linhas
 *        n: número de colunas
 *        nHoles: número de buracos do tabuleiro inicial
 *        posH : Array das posições dos buracos iniciais
 *
 * @return True se o tabuleiro foi resolvido, false caso seja impossível.
 */
bool solvePeg (minINT **tab, int m, int n, ulint nHoles, posArray *posH) {
    int j;
    bool ok;
    ulint jCoord = 0;
    minINT mov, c_mov = 1;
    stack *mem;
    pMovData l_action;
    mem = newStack (pegs-nHoles);

    while (true) {
         j = jCoord;
         /* Enquanto houver peças com movimentos possíves */
         while (j < m*n) {
             ok = false;
             if (tab[j/n][j%n] == 1) {
                mov = c_mov;
                while (mov < 5 && !ok) {
                    if (doMove(tab, m, n, j, mov))
                        ok = true;
                    mov++;
                }
                /* Empilha o movimento e a posição da peça */
                if (ok) {
                    push(mem, j, mov - 1);
                    j = -1;
                }
                c_mov = 1;
             }
             j++;
         }
         /* após sair do loop acima, o tabuleiro não tem mais movimentos
          * possíveis.
          * Há 3 casos possíveis para o tabuleiro:
          * - Ele pode estar correto , então imprime a solução;
          * - A pilha de movimentos pode estar vazia, logo ele é impossível;
          * - Se não for nenhum dos casos acima, ele desempilha o último
          *   movimento e volta ao loop da peça e movimento onde parou. É neste
          *   ponto que o backtracking é feito.
          */

         if (isSolved(posH, tab, nHoles)) {
            printSolution (mem, n);
            destroy(tab, m, posH, mem);
            return true;
        }
         if (isEmpty(*mem)) {
             destroy(tab, m, posH, mem);
             return false;
         }

         /* Backtrack */
         l_action = pop (mem);
         undoMove (tab, m, n, l_action.jCoord, l_action.mov);
         c_mov = l_action.mov + 1;
         jCoord = l_action.jCoord;
    }
}

/*
 * Função: getBoardData
 * --------------------------------------------------------
 *   Retorna um vetor com a quantidade de peças e nHoles , e armazena a posição
 *   de cada buraco.
 * @args  tab: matriz do tabuleiro
 *        m: número de linhas
 *        n: número de colunas
 *
 * @return Vetor de duas posições: [0] = nº de peças e [1] = número de nHoles
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
                addPos (posH, nPos);
            }

    data[0] = pegs;
    data[1] = nHoles;
    return data;
}

/*
 * Função: isSolved
 * --------------------------------------------------------
 *   Verifica se o tabuleiro está resolvido, fazendo primeiro a verificação
 *   mais simples (se nº peças == nº buracos) e chamando uma outra função para
 *   para fazer a segunda verificação caso a primeira seja satisfeita.
 *
 * @args  posH : Array das posições dos buracos iniciais
 *        tab: matriz do tabuleiro
 *        nHoles: número de buracos do tabuleiro inicial
 *
 * @return True se o tabuleiro está resolvido, false caso contrário.
 */
bool isSolved (posArray *posH, minINT **tab, ulint nHoles) {
    /* A primeira condição para que o tabuleiro esteja resolvido é a de que
     * o número de peças seja igual ao número de buracos restantes
     */
    if (pegs == nHoles)
        return allPegsAreHoles (posH, tab);
    return false;
}

/*
 * Função: allPegsAreHoles
 * --------------------------------------------------------
 *   Verifica se há peças onde inicialmente estavam os buracos no tabuleiro
 *   inicial. É a segunda parte da verificação.
 *
 * @args  posH : Array das posições dos buracos iniciais
 *        tab: matriz do tabuleiro
 *
 * @return True se há peças onde haviam buracos. False caso pelo menos uma
 *         posição de buraco inicial não está ocupada por uma peça.
 */
bool allPegsAreHoles (posArray *posH, minINT **tab ) {
    int i;

    for(i = 0; i < posH->i ; i++)
        if(tab[posH->p[i].x][posH->p[i].y] != 1)
            return false;

    return true;
}

/*
 * Função: doMove
 * --------------------------------------------------------
 *   Executa um movimento se ele for possível, atualizando os valores do
 *   tabuleiro.
 *
 * @args  tab: matriz do tabuleiro
 *        m: número de linhas
 *        n: número de colunas
 *        j: posição da peça no tabuleiro
 *        mov : número do movimento
 *
 * @return True se foi possível executar o movimento, false caso contrário.
 */
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

/*
 * Função: undoMove
 * --------------------------------------------------------
 *   Desfaz um movimento, atualizando o tabuleiro para o estado anterior ao
 *   movimento fornecido como argumento.
 *
 * @args  tab: matriz do tabuleiro
 *        m: número de linhas
 *        n: número de colunas
 *        j: posição da peça no tabuleiro
 *        mov : número do movimento
 *
 * @return
 */
void undoMove (minINT **tab, int m, int n, int j, minINT mov) {
    int l = j/n, c = j%n;

    /*Simplesmente desfaz as alterações no tabuleiro */
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

/*
 * Função: canMove
 * --------------------------------------------------------
 *   Verifica se um movimento é possível.
 *
 * @args  tab: matriz do tabuleiro
 *        m: número de linhas
 *        n: número de colunas
 *        j: posição da peça no tabuleiro
 *        mov : número do movimento
 *
 * @return O número do movimento se ele é possível. Caso contrário, retorna 0.
 */
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

/*
 * Função: printSolution
 * --------------------------------------------------------
 *   Imprime a solução no padrão especificado no documento do EP.
 *
 * @args  n: número de colunas
 *        mem : Pilha com as peças e os movimentos efetuados
 *
 * @return
 */
void printSolution (stack *mem, int n) {
    int i,j;
    /* Formato: posição Antiga - nova Posição */
    pos oldP,newP;

    /* Olha as posições na pilha e imprime os movimentos */
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
        printf("%d:%d-%d:%d\n", oldP.x, oldP.y, newP.x, newP.y);
    }
}

/*
 * Função: destroy
 * --------------------------------------------------------
 *   Desaloca estruturas de dados da memória do programa.
 *
 * @args  tab: tabuleiro do jogo
 *        m : Número de linhas
 *        posH : Vetor de posições dos buracos iniciais
 *        mem : Pilha com os movimentos executados
 *
 * @return
 */
void destroy(minINT **tab, int m, posArray *posH, stack *mem) {
    int i;

    for (i = 0; i < m; i++)
        free(tab[i]);
    free (tab);
    free (posH->p);
    destroyStack (mem);
}
