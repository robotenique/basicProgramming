#ifndef __ARRAYOPS_H__
#define __ARRAYOPS_H__
typedef enum { false, true } bool;
typedef char minINT;

typedef struct {
    char* p;
    unsigned int freq;
} word;
/* Data stored. */
typedef union {
  int i;
  char *str;
  void *p;
} EntryData;

/* Return struct for stable_insert. */
typedef struct {
  int new;  /* Was a new entry created? */
  EntryData *data;  /* Data associated with entry. */
} InsertionResult;

void *emalloc(int size);
void die(const char *s);
char *estrdup(const char *s);
int compareAlphabet (const void * a, const void * b);
int compareFreq (const void * a, const void * b);
int linearSearch (char **keys, char* str, int n);
int max(int a, int b);
#endif
