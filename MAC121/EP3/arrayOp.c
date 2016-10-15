/*
 * @author: Juliano Garcia de Oliveira
 * nº usp = 9277086
 * MAC0121
 * 17/10/2016
 * Operações entre arrays e sorting
 */

#include "arrayOp.h"
#include <stdio.h>
#include <stdlib.h>

/* Protótipo de funções */
void swap (int **v, int x, int y);
void toDown (int**v, int n, int i);
void heapify (int **v, int n);

/*
 * Função: toDown
 * --------------------------------------------------------
 * Ajusta um elemento na estrutura de heap. Isto é, rebaixa o elemento
 * até sua posição correta, seguindo as propriedades de um heap.
 * @args v: Matriz do vetor original(v[0]) e posição original (v[1]);
 *       n: Tamanho n do vetor original lido na entrada
 *       i: Posição que deve ser ajustada no heap
 *
 * @return
 */
void toDown (int **v, int n, int i) {
    int x = v[0][i];
    int p = v[1][i];
    int parent = i;
    int son = 2*i + 1;
    while (son < n) {
        if (son + 1 < n && v[0][son + 1] > v[0][son])
            son = son + 1;
        if (x > v[0][son])
            break;
        v[0][parent] = v[0][son];
        v[1][parent] = v[1][son];
        parent = son;
        son = 2*son + 1;
    }
    v[0][parent] = x;
    v[1][parent] = p;

}

/*
 * Função: heapify
 * --------------------------------------------------------
 * Transforma o vetor em um heap.
 * @args v: Matriz do vetor original(v[0]) e posição original (v[1]);
 *       n: Tamanho n do vetor original lido na entrada
 *
 * @return
 */
void heapify (int **v, int n) {
    int i;
    for (i = (n-2)/2; i >=0; toDown(v, n, i), i--);
}

/*
 * Função: heapSort
 * --------------------------------------------------------
 * Ordena a matriz recebida usando o algoritmo de heapSort , que possui
 * complexidade O(n logn)
 *
 * @args v: Matriz do vetor original(v[0]) e posição original (v[1]);
 *       n: Tamanho n do vetor original lido na entrada
 *
 * @return
 */
void heapSort (int **v, int n) {
    int i;
    heapify(v, n);
    for (i = n-1; i > 0; i--){
        swap(v, 0, i);
        toDown(v, i, 0);
    }
}

/*
 * Função: swap
 * --------------------------------------------------------
 * Troca os elementos da coluna x com os da coluna y na matriz
 *
 * @args v: Matriz do vetor original(v[0]) e posição original (v[1]);
 *       n: Tamanho n do vetor original lido na entrada
 *
 * @return
 */
void swap (int **v, int x, int y) {
    /* Dupla troca */
    int aux = v[0][x];
    int aux2 = v[1][x];
    v[0][x] = v[0][y];
    v[1][x] = v[1][y];
    v[0][y] = aux;
    v[1][y] = aux2;
}

/*
 * Função: checkArray
 * --------------------------------------------------------
 * Verifica se a memória do array foi alocada com sucesso. Caso não, exibe
 * uma mensagem de erro e termina o programa.
 *
 * @args v: Um vetor qualquer;
 *
 * @return
 */
void checkArray (int *v) {
    if(v == NULL) {
        printf("ERRO FATAL NA ALOCAÇÃO DE MEMÓRIA! Saindo do programa...\n");
        exit(-1);
    }
}

/*
 * Função: isEqual
 * --------------------------------------------------------
 * Verifica se dois vetores são iguais. Considera que ambos já tem o
 * mesmo tamanho (a verificação deve ser feita antes da chamada)
 *
 * @args a: Um vetor qualquer de tamanho n;
 *       b: Um outro vetor de tamanho n;
 *       n: O tamanho dos vetores;
 *
 * @return true se são iguais, false caso contrário
 */
bool isEqual(int *a, int *b, int n) {
    int i;
    for(i = 0; a[i] == b[i] && i < n; i++);
    return (i == n);
}
