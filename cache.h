#ifndef INC_5LAB_CACHE_H
#define INC_5LAB_CACHE_H
#define MAX_HASH_SIZE 4
#define MAX_CACHE_SIZE 4
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct HashEntry{
    char* key;
    char* value;
    struct HashEntry* prev;
    struct HashEntry* next;
}HashEntry;

typedef struct HashTable{
    int size;
    HashEntry** table;
}HashTable;

unsigned int hash(const char* str);
unsigned int hashFunction(const char* key, int sizeOfTable);
HashTable* hashtableCreation();
void hashtableDeletion(HashTable* table);
int searchingWithin(HashTable* table, const char* key);
void surfaceSearching(HashTable* table, const char* key);
void addToHashtable(HashTable* table, const char* key, const char* value);
#endif
