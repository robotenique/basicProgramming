/*
  stable.h

  A symbol table associating generic data to strings.
*/

#ifndef __STABLE_VD_H__
#define __STABLE_VD_H__
#include "arrayOps.h"

/* The symbol table. */
typedef struct stable_s *SymbolTableVD;

/*
  Return a new symbol table.
*/
SymbolTableVD stable_createVD();

/*
  Destroy a given symbol table.
*/
void stable_destroyVD(SymbolTableVD table);

/*
  Insert a new entry on the symbol table given its key.

  If there is already an entry with the given key, then a struct
  InsertionResult is returned with new == 0 and data pointing to the
  data associated with the entry. Otherwise, a struct is returned with
  new != 0 and data pointing to the data field of the new entry.

  If there is not enough space on the table, or if there is a memory
  allocation error, then crashes with an error message.
*/
InsertionResult stable_insertVD(SymbolTableVD table, const char *key);

/*
  Find the data associated with a given key.

  Given a key, returns a pointer to the data associated with it, or a
  NULL pointer if the key is not found.
*/
EntryData *stable_findVD(SymbolTableVD table, const char *key);

/*
  Visit each entry on the table.

  The visit function is called on each entry, with pointers to its key
  and data. If the visit function returns zero, then the iteration
  stops.

  Returns zero if the iteration was stopped by the visit function,
  nonzero otherwise.
*/
int stable_visitVD(SymbolTableVD table,
            int (*visit)(const char *key, EntryData *data, word *arr, int i),
            word *arr);


#endif
