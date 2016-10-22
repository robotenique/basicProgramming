#include <stdio.h>
#include <stdlib.h>
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
