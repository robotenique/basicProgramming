#include <stdlib.h>
#include <stdio.h>
#include "error.h"

void *emalloc(int size) {
  void *ret;
   ret = malloc(size);
  if (ret == NULL) {
    printf("Error: Call to malloc failed, exit...");
    exit(EXIT_FAILURE);
  }
  return ret;
}
