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

typedef struct {
    word *wArr;
    int i;
} word_BST;

typedef struct inputConfig {
    minINT stableType;
    bool orderByAlpha;
} inputConfig;

void *emalloc(int size);
void die(const char *s);
char *estrdup(const char *s);
int compareAlphabet (const void * a, const void * b);
int compareFreq (const void * a, const void * b);
int linearSearch (char **keys, char* str, int n);
int max(int a, int b);
bool isValid(char c);
bool isNotAlpha(char c);
int  copyValue (const char *key, EntryData *data, word *arr, int i);
void copyValue_BST (const char *key, EntryData *data, word_BST *arr);
#endif
