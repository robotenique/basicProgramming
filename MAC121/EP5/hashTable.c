#include "hashTable.h"

static int pointercmp(const void *pointer1, const void *pointer2);
static unsigned long pointerHashFunction(const void *pointer);

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
