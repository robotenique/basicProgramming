/*
  buffer.h

  A character buffer.
*/

#ifndef __BUFFER_H__
#define __BUFFER_H__
#include <stdio.h>
#include <ctype.h>
#include "arrayOps.h"
#include <stdlib.h>

typedef struct buffer_s {
  char *data;
  int n, i;
} Buffer;


Buffer *buffer_create();

void buffer_destroy(Buffer *B);

void buffer_reset(Buffer *B);

void buffer_push_back(Buffer *B, char c);

int read_line(FILE *input, Buffer *B);

void buffer_lower(Buffer *B);



#endif
