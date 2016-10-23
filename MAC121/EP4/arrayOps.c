#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

int max(int a, int b) { return a > b ? a : b; }
