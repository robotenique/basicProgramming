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


/*
 * Function: HashTableSetKeyComparisonFunction
 * --------------------------------------------------------
 * Especifica a função de comparação das chaves na HashTable.
 * A função especificada deve retornar 0 se são iguais, != 0 caso contrário.
 * A função default é a única que simplesmente compara os pointers.
 *
 * @args    hashTable:  Uma HashTable
 *          keycmp: Função que retorna zero se ambos os argumentos passados
 *                  são considerados chaves "iguais", != 0 caso contrário.
 *
 * @return
 */
void HashTableSetKeyComparisonFunction(HashTable *hashTable,
                             int (*keycmp)(const void *key1, const void *key2));



/*
* Function: HashTableDestroy
* --------------------------------------------------------
* Destrói uma HashTable existente.
*
* @args    hashTable : A HashTable que será destruída
*
* @return
*/
void HashTableDestroy(HashTable *hashTable);


/*
 * Function: HashTableSize
 * --------------------------------------------------------
 * Retorna o número de elementos na HashTable. (O número de elementos
 * "chave" : valor).
 *
 * @args    hashTable: A hashTable
 *
 * @return O número de pares "chave":valor que estão na hashTable.
 */
long HashTableSize(const HashTable *hashTable);
/*
 * Function: HashTableStringHashFunction
 * --------------------------------------------------------
 * Implementação de uma boa função de hash para strings!
 *
 * @args    key: a chave para aplicar o hashing
 *
 * @return O valor do hash para uma determinada chave.
 */
unsigned long HashTableStringHashFunction(const void *key);

/*
 * Function: HashTableGet
 * --------------------------------------------------------
 * Retorna o valor da chava especificada armanada na HashTable
 *
 * @args    hashTable: A hashTable para fazer a busca
 *          key: A chave cujo valor é o procurado
 *
 * @return O valor da chave especificada, ou NULL se a chave não existe na
 *         HashTable
 */
void *HashTableGet(const HashTable *hashTable, const void *key);

/*
 * Function: HashTablePut
 * --------------------------------------------------------
 * Adiciona o valor "key":value especificado como argumento na HashTable.
 * Se a chave já está na HashTable, o valor antigo é sobrescito com o novo
 * valor especificado. Se a tabela está cheia, pode acionar o rehash().
 *
 * @args    hashTable: A HashTable para adicionar o elemento
 *          key: A chave para adicionar / sobrescrever
 *          value: O valor associado com a chave
 *
 * @return 0 caso houve sucesso, -1 se houve erro.
 */
int HashTablePut(HashTable *hashTable, const void *key, void *value);

#endif
