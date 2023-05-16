#include "cache.h"
#include "functionsForFile.h"
unsigned int hash(const char* str){
    unsigned int hash = 0;
    while (*str){
        hash = hash * 101 + *str++;
    }
    return hash;
}
unsigned int hashFunction(const char* key, int sizeOfTable){
    return hash(key) % sizeOfTable;
}
HashTable* hashtableCreation(){
    HashTable* table = malloc(sizeof(HashTable));
    table->size = MAX_HASH_SIZE;
    table->table = malloc(sizeof(HashEntry*) * table->size);
    for (int i = 0; i < table->size; i++){
        table->table[i] = NULL;
    }
    return table;
}
int searchingWithin(HashTable* table, const char* key){
    unsigned int index = hashFunction(key, table->size);
    HashEntry* current = table->table[index];
    HashEntry* prev = NULL;
    while (current != NULL){
        if (strcmp(current->key, key) == 0){
            printf("\033[0;33mFound IP Address\033[0m: %s\n", current->value);
            if (prev != NULL) {
                prev->next = current->next;
                if (current->next != NULL){
                    current->next->prev = prev;
                }
                current->prev = NULL;
                current->next = table->table[index];
                table->table[index]->prev = current;
                table->table[index] = current;
            }
            HashEntry* next = current->next;
            while (next != NULL){
                next->prev = next->prev == current ? NULL : current;
                current->next = next;
                current->prev = prev;
                prev = current;
                current = next;
                next = next->next;
            }
            return 1;
        }
        prev = current;
        current = current->next;
    }
    return 0;
}
void surfaceSearching(HashTable* table, const char* key){
    if(searchingWithin(table, key) == 0){
        ipSearch(table, "listOfDNSAndIP.txt", key, NULL);
    }else{
        return;
    }
    searchingWithin(table, key);
}
void addToHashtable(HashTable* table, const char* key, const char* value){
    unsigned int index = hashFunction(key, table->size);
    HashEntry* set = malloc(sizeof(HashEntry));
    set->key = strdup(key);
    set->value = strdup(value);
    int count = 0;
    if(table->table[index] != NULL){
        HashEntry* current = table->table[index];
        while(current != NULL){
            count++;
            if(count >= MAX_CACHE_SIZE-1 && current->next != NULL){
                printf("Removing %s\n", current->next->key);
                free(current->next);
                current->next = NULL;
                break;
            }
            current = current->next;
        }
    }
    set->prev = NULL;
    set->next = table->table[index];
    if (table->table[index] != NULL){
        table->table[index]->prev = set;
    }
    table->table[index] = set;
}
void hashtableDeletion(HashTable* table) {
    for (int i = 0; i < table->size; i++) {
        HashEntry* current = table->table[i];
        while (current != NULL) {
            HashEntry* next = current->next;
            free(current->key);
            free(current->value);
            free(current);
            current = next;
        }
    }
    free(table->table);
    free(table);
}