#ifndef __ARRAYOPS_H__
#define __ARRAYOPS_H__
typedef enum { false, true } bool;
typedef char minINT;
void *emalloc(int size);
void die(const char *s);
char *estrdup(const char *s);
typedef struct {
    char* p;
    unsigned int freq;
} word;
int compareAlphabet (const void * a, const void * b);
int compareFreq (const void * a, const void * b);
int max(int a, int b); 
#endif
