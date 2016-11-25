#include <stdlib.h>
#include "error.h"
#include "hashTable.h"
static int pointercmp(const void *pointer1, const void *pointer2);
static unsigned long pointerHashFunction(const void *pointer);
static long getNumBuckets(HashTable *hashTable);
static int isProbablePrime(long number);
void HashTableRehash(HashTable *hashTable, long numOfBuckets);


HashTable *HashTableCreate(long numOfBuckets) {
    int i;
    HashTable *hTable;
    if(numOfBuckets <= 0) return NULL;
    hTable = (HashTable *)emalloc(sizeof(HashTable));
    hTable->bucketArray = (KeyValuePair **)emalloc(numOfBuckets *
                            sizeof(KeyValuePair *));
    hTable->numOfBuckets = numOfBuckets;
    hTable->numOfElements = 0;

    for(i = 0; i < numOfBuckets; i++)
        hTable->bucketArray[i] = NULL;

    hTable->idealRatio = 3.0;
    hTable->lowerRehashThreshold = 0.0;
    hTable->upperRehashThreshold = 15.0;
    hTable->keycmp = pointercmp;
    hTable->valuecmp = pointercmp;
    hTable->hashFunction = pointerHashFunction;
    hTable->keyDeallocator = NULL;
    hTable->valueDeallocator = NULL;

    return hTable;
}

static int pointercmp(const void *pointer1, const void *pointer2) {
    return (pointer1 != pointer2);
}

static unsigned long pointerHashFunction(const void *pointer) {
    return ((unsigned long) pointer) >> 4;
}

void HashTableSetHashFunction(HashTable *hashTable,
                             unsigned long (*hashFunction)(const void *key)) {
    if(hashFunction == NULL) return;
    hashTable->hashFunction = hashFunction;
}

void HashTableSetDeallocationFunctions(HashTable *hashTable,
                                        void (*keyDeallocator)(void *key),
                                        void (*valueDeallocator)(void *value)) {
    hashTable->keyDeallocator = keyDeallocator;
    hashTable->valueDeallocator = valueDeallocator;
}

void HashTableSetKeyComparisonFunction(HashTable *hashTable,
                             int (*keycmp)(const void *key1, const void *key2)) {
    if(keycmp == NULL) return;
    hashTable->keycmp = keycmp;

}

void HashTableDestroy(HashTable *hashTable) {
    int i;
    KeyValuePair *pair, *nextPair;
    for(i = 0; i < hashTable->numOfBuckets; i++) {
        pair = hashTable->bucketArray[i];
        while(pair != NULL) {
            nextPair = pair->next;
            if(hashTable->keyDeallocator != NULL)
                hashTable->keyDeallocator((void *) pair->key);
            if (hashTable->valueDeallocator != NULL)
                hashTable->valueDeallocator(pair->value);
            free(pair);
            pair = nextPair;
        }
    }
    free(hashTable->bucketArray);
    free(hashTable);
}

long HashTableSize(const HashTable *hashTable) {
    return hashTable->numOfElements;
}

unsigned long HashTableStringHashFunction(const void *key) {
    unsigned long h;
    const unsigned char *str;
    int c;
    str = (const unsigned char *) key;
    h = 5381;
    /* Implementação do algoritmo djb2 */
    while ((c = *str++) != '\0')
        h = h*33 + c;

    return h;
}

void *HashTableGet(const HashTable *hashTable, const void *key) {
    long hValue;
    KeyValuePair *pair;
    hValue = hashTable->hashFunction(key) % hashTable->numOfBuckets;
    pair = hashTable->bucketArray[hValue];
    while (pair != NULL && hashTable->keycmp(key, pair->key) != 0)
        pair = pair->next;

    return (pair == NULL) ? NULL : pair->value;
}

int HashTablePut(HashTable *hashTable, const void *key, void *value) {
    long hValue;
    float aux;
    KeyValuePair *pair, *newPair;
    if(key == NULL || value == NULL) return -1;
    hValue = hashTable->hashFunction(key) & hashTable->numOfBuckets;
    pair = hashTable->bucketArray[hValue];

    while(pair != NULL && hashTable->keycmp(key, pair->key) != 0)
        pair = pair->next;

    if(pair) {
        if (pair->key != key) {
            if(hashTable->keyDeallocator != NULL)
                hashTable->keyDeallocator((void *)pair->key);
            pair->key = key;
        }
        if(pair->value != value) {
            if(hashTable->valueDeallocator != NULL)
                hashTable->valueDeallocator(pair->value);
            pair->value = value;
        }
    }
    else {
        newPair = (KeyValuePair *)emalloc(sizeof(KeyValuePair));
        newPair->key = key;
        newPair->value = value;
        newPair->next = hashTable->bucketArray[hValue];
        hashTable->bucketArray[hValue] = newPair;
        hashTable->numOfElements++;

        if(hashTable->upperRehashThreshold > hashTable->idealRatio) {
            aux = (float)hashTable->numOfElements/(float)hashTable->numOfBuckets;
            if(aux > hashTable->upperRehashThreshold)
                HashTableRehash(hashTable, 0);
        }
    }
    return 0;
}

/*
 * Function: HashTableRehash
 * --------------------------------------------------------
 * Reorganiza a HashTable para ser mais eficiente. Se o número "buckets" é
 * especificado, a hashTable é "rehasheada" para o número passado como
 * parâmetro. Se o número recebido é 0, então é a hashTable é "rehasheada"
 * para uma quantidade que é automaticamente calculado para ser um número
 * primo que chega mais próximo da constate especificada na struct da
 * hashTable (o membro : 'idealRatio').
 *
 * @args    hashTable: A hashTable que será reorganizada
 *          numOfBuckets: Tamanho para fazer o hash. Deve ser primo.
 *                        (ver HashTableCreate para mais explicações).
 *
 * @return
 */
void HashTableRehash(HashTable *hashTable, long numOfBuckets) {
    int i;
    long hashValue;
    KeyValuePair **newBucketArray, *pair, *nextPair;

    if(numOfBuckets < 0) exit(EXIT_FAILURE);
    if (numOfBuckets == 0)
        numOfBuckets = getNumBuckets(hashTable);

    if (numOfBuckets == hashTable->numOfBuckets)
        return; /* Já está no tamanho correto */

    newBucketArray = malloc(numOfBuckets * sizeof(KeyValuePair *));
    if (newBucketArray == NULL) return; /* Não é possível rehash */

    for (i = 0; i < numOfBuckets; i++)
        newBucketArray[i] = NULL;

    /* Calcula o hash novamente para cada entrada no novo Array */
    for (i=0; i < hashTable->numOfBuckets; i++) {
        pair = hashTable->bucketArray[i];
        while (pair != NULL) {
            nextPair = pair->next;
            hashValue = hashTable->hashFunction(pair->key) % numOfBuckets;
            pair->next = newBucketArray[hashValue];
            newBucketArray[hashValue] = pair;
            pair = nextPair;
        }
    }
    /* Coloca o novo array de hash na tabela */
    free(hashTable->bucketArray);
    hashTable->bucketArray = newBucketArray;
    hashTable->numOfBuckets = numOfBuckets;
}

static long getNumBuckets(HashTable *hashTable) {
    long idealNum = hashTable->numOfElements / hashTable->idealRatio;
    if (idealNum < 5)
        idealNum = 5;
    else
        idealNum |= 0x01; /* Transforma em número par */
    while (!isProbablePrime(idealNum))
        idealNum += 2;

    return idealNum;
}

static int isProbablePrime(long number) {
    long i;
    for(i = 3; i < 51; i+= 2)
        if(number == i)
            return 1;
        else if(number%i == 0)
            return 0;
    return 1; /* Provavelmente D: */
}
