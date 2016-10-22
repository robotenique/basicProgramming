/*
  stable.h

  A symbol table associating generic data to strings.
*/

#ifndef __STABLE_H__
#define __STABLE_H__

// The symbol table.
typedef struct stable_s *SymbolTableVD;

// Data stored.
typedef union {
  int i;
  char *str;
  void *p;
} EntryData;

// Return struct for stable_insert.
typedef struct {
  int new;  // Was a new entry created?
  EntryData *data;  // Data associated with entry.
} InsertionResult;

/*
  Return a new symbol table.
*/
SymbolTableVD stable_create();

/*
  Destroy a given symbol table.
*/
void stable_destroy(SymbolTableVD table);

/*
  Insert a new entry on the symbol table given its key.

  If there is already an entry with the given key, then a struct
  InsertionResult is returned with new == 0 and data pointing to the
  data associated with the entry. Otherwise, a struct is returned with
  new != 0 and data pointing to the data field of the new entry.

  If there is not enough space on the table, or if there is a memory
  allocation error, then crashes with an error message.
*/
InsertionResult stable_insert(SymbolTableVD table, const unsigned char *key);

/*
  Find the data associated with a given key.

  Given a key, returns a pointer to the data associated with it, or a
  NULL pointer if the key is not found.
*/
EntryData *stable_find(SymbolTableVD table, const unsigned char *key);

/*
  Visit each entry on the table.

  The visit function is called on each entry, with pointers to its key
  and data. If the visit function returns zero, then the iteration
  stops.

  Returns zero if the iteration was stopped by the visit function,
  nonzero otherwise.
*/
int stable_visit(SymbolTableVD table,
                 int (*visit)(const unsigned char *key, EntryData *data));


#endif
