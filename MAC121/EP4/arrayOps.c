/*
 * @author: Juliano Garcia de Oliveira
 * nº usp = 9277086
 * MAC0121
 * 14/11/2016
 * Funções auxiliares para a tabela de símbolos e leitura.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "arrayOps.h"

/* Funções de tratamento de erros */

void *emalloc(int size) {
  void *ret;
   ret = malloc(size);
  if (ret == NULL) {
    printf("Error: Call to malloc failed, exit...");
    exit(-1);
  }
  return ret;
}

void die(const char *s) {
    printf("%s\n", s);
    exit(-1);
}

char *estrdup(const char *s) {
  char *ret = malloc(strlen(s) + 1);
  if (ret == NULL)
    die("Error: Failed to duplicate string, exit...");
  strcpy(ret, s);
  return ret;
}

int compareAlphabet (const void * a, const void * b) {
  return strcmp(((word *)a)->p, ((word *)b)->p);
}

int compareFreq (const void * a, const void * b) {
    int freqA = ((word *)a)->freq;
    int freqB = ((word *)b)->freq;
    if(freqA < freqB)
        return 1;
    else if(freqA > freqB)
        return -1;
    return compareAlphabet(a,b);
}

int linearSearch (char **keys, char* str, int n) {
    int i;
    for (i = 0; i < n; i++) {
       if (strcmp(keys[i], str) == 0)
           return i;
   }
   return -1;
}

bool isValid(char c)  {
    return isalpha(c) || isdigit(c);
}

bool isNotAlpha(char c) {
    return isdigit(c) || !isalpha(c);
}

int copyValue(const char *key, EntryData *data, word *arr, int i) {
    arr[i].p = estrdup(key);
    arr[i].freq = data->i;
    return 1;
}

int max(int a, int b) {
    return a > b ? a : b;
}

void copyValue_BST (const char *key, EntryData *data, word_BST *arr) {
    arr->wArr[arr->i].p = estrdup(key);
    arr->wArr[arr->i++].freq = data->i;
}
