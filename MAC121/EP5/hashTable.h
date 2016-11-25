/* Implementação de HashTable */
/*
 * Simplificação da implementação de HashTable por Keith Pomakis
 * (pomakis@pobox.com), Agosto, 1998 (Public domain).
 */

#ifndef _HASH_TABLE_H
#define _HASH_TABLE_H

/* Não devem ser acessadas diretamente, só através de funções..*/
typedef struct keyVal {
    const void *key;
    void *value;
    struct keyVal *next;
} KeyValuePair;

typedef struct {
    long numOfBuckets;
    long numOfElements;
    KeyValuePair **bucketArray;
    float idealRatio, lowerRehashThreshold, upperRehashThreshold;
    int (*keycmp)(const void *key1, const void *key2);
    int (*valuecmp)(const void *value1, const void *value2);
    unsigned long (*hashFunction)(const void *key);
    void (*keyDeallocator)(void *key);
    void (*valueDeallocator)(void *value);
} HashTable;

/*
 * Function: HashTableCreate
 * --------------------------------------------------------
 * Cria uma nova HashTable. A HashTable deve ser destruída explicitamente após
 * o uso.
 *
 * @args    numOfBuckets: Número do tamanho para começar a HashTable. Deve ser
 *                        maior que zero, e primo. Idealmente, esse número deve
 *                        ser entre 1/5 e 1 vezes maior que o número de elementos
 *                        esperados na HashTable.
 *
 * @return Uma nova HashTable, NULL se houve erro.
 */
HashTable *HashTableCreate(long numOfBuckets);

HashTableSetKeyComparisonFunction(transTable, alpha_beta_keycmp);

/*
 * Function: HashTableSetHashFunction
 * --------------------------------------------------------
 * Especifica a função de hash usada pela Hash Table.
 *
 * @args    hashTable:  A hashTable cuja função foi especificada
 *          hashFunction : Ponteiro para uma função que retorna um hashCode
 *                         adequado para uma dada chave (key)
 *
 * @return
 */

void HashTableSetHashFunction(HashTable *hashTable,
                             unsigned long (*hashFunction)(const void *key));

/*
 * Function: HashTableSetDeallocationFunctions
 * --------------------------------------------------------
 * Especifica as funções de desalocação  da chave e do valor da HashTable.
 * Essas funções determinam o que acontece quando uma chave ou valor é removido
 * da HashTable. Se a função de desalocação é NULL (o default), então a
 * referência é simplesmente retirada da tabela, e o gerenciamento de memória
 * deve ser feito pelo programa principal. Se a função é != NULL, ela é chamada
 * para liberar a memória usada pelo objeto. (OBS: Para objetos simples, é
 * suficiente usar a função free())
 *
 * @args    hashTable:  Uma HashTable
 *          hashFunction : Ponteiro para uma função que retorna um hashCode
 *                         adequado para uma dada chave (key)
 *          keyDeallocator: Se != NULL, é a função que será chamada quando a
 *                          chave for removida da HashTable
 *          valueDeallocator: Se != NULL, a função chamada quando o valor
 *                            é removido da HashTable.
 *
 * @return
 */
void HashTableSetDeallocationFunctions(HashTable *hashTable,
                                        void (*keyDeallocator)(void *key),
                                        void (*valueDeallocator)(void *value));


/*--------------------------------------------------------------------------*\
 *  NAME:
 *      HashTableSetKeyComparisonFunction()
 *              - specifies the function used to compare keys in a HashTable
 *  DESCRIPTION:
 *      Specifies the function used to compare keys in the specified
 *      HashTable.  The specified function should return zero if the two
 *      keys are considered equal, and non-zero otherwise.  The default
 *      function is one that simply compares pointers.
 *  ARGUMENTS:
 *      hashTable    - the HashTable whose key comparison function is being
 *                     specified
 *      keycmp       - a function which returns zero if the two arguments
 *                     passed to it are considered "equal" keys and non-zero
 *                     otherwise
 *  RETURNS:
 *      <nothing>
\*--------------------------------------------------------------------------*/

/*
 * Function: HashTableSetKeyComparisonFunction
 * --------------------------------------------------------
 * Especifica a função de comparação das chaves na HashTable.
 * A função especificada deve retornar 0 se são iguais, != 0 caso contrário.
 * A função default é a única que simplesmente compara os pointers.
 *
 * @args    hashTable:  Uma HashTable
 *          hashFunction : Ponteiro para uma função que retorna um hashCode
 *                         adequado para uma dada chave (key)
 *          keyDeallocator: Se != NULL, é a função que será chamada quando a
 *                          chave for removida da HashTable
 *          valueDeallocator: Se != NULL, a função chamada quando o valor
 *                            é removido da HashTable.
 *
 * @return
 */
void HashTableSetKeyComparisonFunction(HashTable *hashTable,
                             int (*keycmp)(const void *key1, const void *key2));


#endif
