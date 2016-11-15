/*
 * @author: Juliano Garcia de Oliveira
 * nº usp = 9277086
 * MAC0121
 * 14/11/2016
 * Implementação da tabela de símbolos usando Árvore de Busca Binária.
 */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "tabelaSimbolo_AB.h"
#include "arrayOps.h"

/* Cada entrada da tabela possui:
 * key: A chave da tabela de símbolos, é sempre única.
 * data: O dado da respectiva chave.
 * left e right: ponteiros para as subárvores da esquerda e da direita.
 */
typedef struct entryST {
    char *key;
    EntryData data;
    struct entryST *left, *right;
} Entry;

/* A tabela de símbolos contém o ponteiro para  a primeira
 * entrada da tabela (a raiz).
 */
struct stable_s {
    Entry *root;
};

/*
 * Função: createST_AB
 * --------------------------------------------------------
 * Cria a tabela de símbolos (AB). No caso de uma árvore de busca binária,
 * só aloca a estrutura de dado e faz com que a raiz receba NULL, indicando
 * que a tabela está vazia.
 *
 * @args
 *
 * @return Uma tabela de símbolos (AB) vazia.
 */
SymbolTableAB createST_AB() {
    SymbolTableAB t = emalloc(sizeof(struct stable_s));
    t -> root = NULL;
    return t;
}

/*
 * Função: destroySubTree
 * --------------------------------------------------------
 * Destrói subárvores recursivamente, destruindo toda a árvore embaixo da
 * 'root'. Se é passada a raiz principal da árvore da tabela de símbolos,
 * destrói a tabela inteira.
 *
 * @args    root: Ponteiro para a raiz da árvore
 *
 * @return
 */
void destroySubTree(Entry *root) {
    if(root != NULL) {
        destroySubTree(root->right);
        destroySubTree(root->left);
        free(root->key);
        free(root);
    }
}

/*
 * Função: destroyST_AB
 * --------------------------------------------------------
 * Libera toda a memória alocada pela tabela de símbolos (AB),
 * usando a função destroySubTree para desalocar recursivamente
 * cada subárvore da tabela.
 *
 * @args    table: Tabela de símbolos (AB)
 *
 * @return
 */
void destroyST_AB(SymbolTableAB table) {
    destroySubTree(table->root);
    free(table);
}

/*
 * Função: insertRec
 * --------------------------------------------------------
 * Insere recursivamente um elemento na árvore binária da tabela,
 * retornando a raiz da árvore, e modificando o Insertion Result passado
 * como argumento.
 *
 * @args    root: Ponteiro para a raiz da árvore
 *          key:  Chave a ser inserida na árvore
 *          ir: Ponteiro para um Insertion Result
 *
 * @return Ponteiro para a raiz da árvore
 */
Entry * insertRec (Entry *root, char *key, InsertionResult *ir) {
    Entry *new;
    int cmp;
      if (root == NULL) {
          new = emalloc(sizeof(Entry));
          new->key = key;
          new->data.i = 0;
          ir->new = 1;
          ir->data = &(new->data);
          new->left = NULL;
          new->right = NULL;
          return new;
      }
    cmp = strcmp(key, root->key);
    if (cmp < 0)
        root->left  = insertRec(root->left, key, ir);
    else if(cmp > 0)
        root->right = insertRec(root->right, key, ir);
    else
        ir->data = &(root->data);
    return root;
}

/*
 * Função: insertST_AB
 * --------------------------------------------------------
 * Função que insere um elemento na tabela de símbolos (AB) se o elemento
 * não estiver na tabela. Se estiver, o elemento não é inserido.
 *
 * @args    table: Tabela de Símbolos (AB)
 *          key:   Nova chave para ser inserida na tabela
 *
 * @return Um Insertion Result com os dados da inserção.
 */
InsertionResult insertST_AB(SymbolTableAB table, const char *key) {
    InsertionResult ir;
    char *cpy;
    ir.new = 0;
    table->root = insertRec(table->root, cpy = estrdup(key), &(ir));
    if(ir.new == 0)
        free(cpy);
    return ir;
}

/*
 * Função: apply_InOrder
 * --------------------------------------------------------
 * Aplica a função de nome 'apply' em cada elemento da tabela, percorrendo
 * a árvore usando 'inOrder'. Esta é uma função recursiva.
 *
 * @args    root:   Raiz da árvore
 *          apply:  Ponteiro para a função
 *          arr:    Ponteiro para um array de pares {palavra:frequência, total}
 *
 * @return
 */
void apply_InOrder(Entry *root,
            void (*apply)(const char *key, EntryData *data, word_BST *arr),
            word_BST *arr) {
    if(root == NULL)
        return;
    apply_InOrder(root->left, apply, arr);
    apply(root->key, &(root->data), arr);
    apply_InOrder(root->right, apply, arr);

}

/*
 * Função: applyST_AB
 * --------------------------------------------------------
 * Para cada elemento da árvore, aplica a função 'apply'. Usa a função
 * apply_InOrder.
 *
 * @args    table:  Tabela de símbolos (AB)
 *          apply:  Ponteiro para a função
 *          arr:    Ponteiro para um array de pares {palavra:frequência, total}
 *
 * @return
 */
void applyST_AB(SymbolTableAB table,
            void (*apply)(const char *key, EntryData *data, word_BST *arr),
            word_BST *arr) {
    apply_InOrder(table->root, apply, arr);
}
