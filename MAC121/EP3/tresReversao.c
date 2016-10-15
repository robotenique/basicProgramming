/*
 * @author: Juliano Garcia de Oliveira
 * nº usp = 9277086
 * MAC0121
 * 17/10/2016
 * Arquivo principal
 */
#include <stdlib.h>
#include <stdio.h>
#include "arrayOp.h"

/* Protótipo de funções */
bool sortArray (int **v, int n);
void bSortOdd (int **v, int **s, int n);
int mod(int a, int b);
void swapElements (int **v, int **s, int x, int y);
void swapPos (int *v, int x, int y);
void bubble3(int *array, int n, int ini);
void fixPos (int *v, int *s, int i);


/*
 * Função: main
 * --------------------------------------------------------
 * Lê os dados da entrada padrão, inicializa variáveis e chama a função para
 * tentar ordenar o vetor circular lido.
 * @args
 *
 * @return retorno padrão da linguagem C.
 */
int main(int argc, char const *argv[]) {
    int n, i;
    int **v;

    /* Leitura */
    scanf("%d",&n);
    v = malloc(3*sizeof(int*));
    if(v == NULL) exit(-1);
    v[0] = malloc(n*sizeof(int));
    v[1] = malloc(n*sizeof(int));
    for (i = 0; i < 2; checkArray(v[i]), i++);
    /* Preenche o vetor */
    for (i = 0; i < n; i++) {
        scanf("%d", &v[0][i]);
        v[1][i] = i;
    }

    /* Chama a função sortArray(v,n) se n >= 3 */
    if(n < 3 || !sortArray(v, n))
        printf("Nao e possivel\n");
    return 0;
}


/*
 * Função: sortArray
 * --------------------------------------------------------
 * Faz verificações se é possível ou não ordenar o vetor usando 3 rotações.
 * Se é possível, imprime as sequências de 3 rotações que ordenam o vetor.
 * Se não é possível, simplesmente retorna falso.
 *
 * @args   v: Matriz do vetor original(v[0]) e posição original (v[1]);
 *         n: Tamanho do vetor;
 *
 * @return true se foi possível ordenar, false caso contrário
 */
bool sortArray (int **v, int n) {
    int k;
    /* Faz uma cópia do vetor original */
    int **s = malloc(2*sizeof(int*));
    s[0] = malloc(n*sizeof(int));
    s[1] = malloc(n*sizeof(int));
    if(s == NULL) exit(-1);
    for (k = 0; k < 2; checkArray(v[k]), k++);
    /* Copiando dados */
    for (k = 0; k < n; s[0][k] = v[0][k], s[1][k] = k, k++);
    /* Faz um sort O(nlogn) no vetor */
    heapSort(s, n);

    /* Se o vetor é par, verifica se é possível. */
    if (!(n % 2)) {
        for (k = 0; k < n && (s[1][k] % 2 == v[1][k] % 2); k++);
        if (k != n)
            return false;
        /* Se o vetor é possível, ordena primeiro as posições pares,
         * e depois ordena as posições ímpares, ambas com o bubble3.
         */
        if(!isEqual(v[0], s[0], n)) {
            bubble3(v[0],n,0);
            if(!isEqual(v[0], s[0], n))
                bubble3(v[0],n,1);
        }

    }
    /* Se o vetor é ímpar, preenche v[1] com os endereços corretos e
     * chama a função para ordenar vetores ímpares.
     */
    else {
        for (k = 0; k < n; v[1][s[1][k]] = k, k++);
        bSortOdd (v, s, n);
    }
    return true;
}

/*
 * Função: bSortOdd
 * --------------------------------------------------------
 * Ordena o vetor v[0] e vai imprimindo os movimentos necessários para
 * ordenar o vetor circular usando movimentos de 3 rotações.
 *
 * @args   v: Matriz do vetor original (v[0]) e endereços para vetor
 *            ordenado (v[1]);
 *         s: Matriz do vetor ordenado (s[0]) e endereços para vetor
 *            original (s[1]);
 *         n: Tamanho do vetor;
 *
 * @return
 */
void bSortOdd (int **v, int **s, int n) {
    int total = n, i, pos;
    bool flag; /* Variável de controle */
    /* Posição a ser preenchida na iteração */
    i = mod(n - 2 , n);

    /* Preciso rodar no máximo n-1 vezes */
    while(total > 1) {
    /* Posição do elemento que deve ir para posição i */
        pos = s[1][i];
        flag = false;
        /* Enquanto não houver o número correto na posição i*/
        while (v[0][i] != s[0][i]) {
            flag = true;
            /* Faz a 3-rotação */
            swapElements(v, s, pos, mod(pos + 2, n));
            printf("%d\n", pos);
            pos = mod(pos + 2, n);
        }
        /* Caso seja necessário, corrije os índices */
         if(!flag)
            fixPos(v[1], s[1], i);

        i = mod(i - 2, n);
        total--;
    }
}


/* Funções auxiliares e secundárias */


/*
 * Função: bubble3
 * --------------------------------------------------------
 * É um simples bubbleSort modificado que faz um sorting usando a 3-rotação.
 * Ao invés de comparar 'i' com 'i + 1' (como no original), esta versão
 * compara o elemento 'i' com '(i + 2) % n'.
 *
 * @args   v: Vetor com os elementos para ordenar;
 *         n: Tamanho do vetor;
 *         ini: Posição do elemento onde começa o bubbleSort.
 *
 * @return
 */
void bubble3(int *v, int n, int ini) {
    int i, j, temp;
    bool flag;
    for(i = ini; i < n; i++) {
       flag = false;
       for(j = 0; j < n - i - 1; j++) {
          if(v[j] > v[mod(j + 2, n)]) {
            flag = true;
            temp = v[mod(j + 2, n)];
            v[mod(j + 2, n)] = v[j];
            v[j] = temp;
            printf ("%d\n", j);
          }
       }
      if(!flag)
         return;
   }
}

/*
 * Função: fixPos
 * --------------------------------------------------------
 * Arruma as posições que os endereços de v[1] e s[1] apontam. Isso só
 * é necessário quando um elemento já está na sua posição final no vetor
 * ordenado, então não é preciso trocar o elemento, mas apenas os endereços
 * para onde aponta.
 *
 * @args   v: Vetor com os endereços para vetor ordenado (s[0]);
 *         s: Vetor com os endereços para vetor original (v[0]);
 *         n: Tamanho do vetor;
 *
 * @return
 */
void fixPos (int *v, int *s, int i) {
    /* Dupla troca de valores */
    int aux1, aux2;
    aux1 = s[i];
    aux2 = v[i];
    s[i] = i;
    s[aux2] = aux1;
     v[i] = i;
    v[aux1] = aux2;
}

/*
 * Função: swapElements
 * --------------------------------------------------------
 * Troca o elemento da posição 'x' com o elemento da posição 'y' no
 * vetor v[0], troca os endereços no vetor ordenado (s) e troca os
 * endereços do vetor original (v)
 *
 * @args   v: Matriz do vetor original (v[0]) e endereços para vetor
 *            ordenado (v[1]);
 *         s: Matriz do vetor ordenado (s[0]) e endereços para vetor
 *            original (s[1]);
 *         x: posição do primeiro elemento para trocar
 *         y: posição do segundo elemento para trocar
 *
 * @return
 */
void swapElements (int **v, int **s, int x, int y) {
    /* Dupla troca usando variáveis auxiliares */
    int aux1 = v[1][x], aux2 = s[1][v[1][x]];
    swapPos(v[0],x,y);
    s[1][v[1][x]] = s[1][v[1][y]];
    s[1][v[1][y]] = aux2;
    v[1][x] = v[1][y];
    v[1][y] = aux1;
}
/*
 * Função: mod
 * --------------------------------------------------------
 * Calcula o módulo entre 2 números 'a' e 'b', e retorna o resultado.
 * Ela calcula o modúlo do mesmo jeito que o Python, ou seja, não retorna
 * número negativos quando a < 0 e b > 0
 *
 * @args   a: inteiro
 *         b: inteiro
 *
 * @return (a % b) se a >= 0, (b + a) % b caso contrário.
 */
int mod (int a, int b) {
    if(a >= 0)
        return a % b;
    return (b + a) % b;
}

/*
 * Função: swapPos
 * --------------------------------------------------------
 * Troca o elemento da posição 'x' com o elemento da posição 'y' em um
 * vetor v.
 *
 * @args   v: vetor
 *         x: posição do primeiro elemento para trocar
 *         y: posição do segundo elemento para trocar
 *
 * @return
 */
void swapPos (int *v, int x, int y) {
   int aux = v[x];
   v[x] = v[y];
   v[y] = aux;
}
