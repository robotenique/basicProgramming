#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "tabelaSimbolo_AB.h"
#include "arrayOps.h"

typedef struct entryST {
    char *key;
    EntryData data;
    struct entryST *left, *right;
} Entry;

struct stable_s {
    Entry *root;
};

SymbolTableAB createST_AB() {
    SymbolTableAB t = emalloc(sizeof(struct stable_s));
    t -> root = NULL;
    return t;
}

void destroySubTree(Entry *root) {
    if(root != NULL) {
        destroySubTree(root->right);
        destroySubTree(root->left);
        free(root->key);
        free(root);
    }
}

void destroyST_AB(SymbolTableAB table) {
    destroySubTree(table->root);
    free(table);
}


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

InsertionResult insertST_AB(SymbolTableAB table, const char *key) {
    InsertionResult ir;
    char *cpy;
    ir.new = 0;
    table->root = insertRec(table->root, cpy = estrdup(key), &(ir));
    if(ir.new == 0)
        free(cpy);
    return ir;
}

void apply_InOrder(Entry *root,
            void (*apply)(const char *key, EntryData *data, word_BST *arr),
            word_BST *arr) {
    if(root == NULL)
        return;
    apply_InOrder(root->left, apply, arr);
    apply(root->key, &(root->data), arr);
    apply_InOrder(root->right, apply, arr);

}


void applyST_AB(SymbolTableAB table,
            void (*apply)(const char *key, EntryData *data, word_BST *arr),
            word_BST *arr) {
    apply_InOrder(table->root, apply, arr);
}
