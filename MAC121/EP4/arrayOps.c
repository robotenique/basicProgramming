#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "arrayOps.h"
void *emalloc(int size) {
  void *ret;
   ret = malloc(size);
  if (!ret) {
    printf("call to malloc failed!");
    exit(-1);
  }
  return ret;
}

void die(const char *s) {
    printf("%s\n",s );
    exit(-1);
}
char *estrdup(const char *s) {
  char *ret = malloc(strlen(s) + 1);

  if (!ret)
    die("Error: call to strdup failed, exiting program...");
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
    return 0;
}

/* Check if a key is in the 'keys' array */
int linearSearch (char **keys, char* str, int n) {
    int i;
    for (i = 0; i < n; i++) {
       if (strcmp(keys[i], str) == 0)
           return i;
   }
   /* We didn't find the str in the keys array */
   return -1;
}
/* Funções auxiliares */
bool isValid(char c)  { return isalpha(c) || isdigit(c); }
bool isNotAlpha(char c) {
    return isdigit(c) || !isalpha(c);
}
int max(int a, int b) { return a > b ? a : b; }
