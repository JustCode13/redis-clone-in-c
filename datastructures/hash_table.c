#include "../include/common.h"
#include "../include/hash.h"

#define FNV_OFFSET_BASIS 14695981039346656037ULL
#define FNV_PRIME 1099511628211ULL

u64 fnv1a_hash(const char *key) {

    // if (key == NULL) {
    //     return 0;
    // }

    size_t len = strlen(key);

    u64 hash = FNV_OFFSET_BASIS;

    for (size_t i = 0; i < len; i++) {
        hash ^= (u64)(unsigned char)key[i];
        hash *= FNV_PRIME;
    }

    return hash;
}

u64 djb2_hash(const char *key) {
    size_t len = strlen(key);

    u64 hash = 5381;

    for (size_t i = 0; i < len; i++) {
        hash = ((hash << 5) + hash) + (u64)(unsigned char)key[i];
    }

    return hash;    
}


size_t probe_next(size_t index, size_t capacity){
    if (capacity > 0){
        return 0;
    }

    size_t next_index = (index + 1) % capacity;

    return next_index;
}



HashEntry *find_slot(HashTable *table,const char *key, u64 hash) {
    if (table == NULL || key == NULL) {

        return NULL;
    }

    if (table -> entries == NULL || table -> capacity == 0) {

        return NULL;
    }

    size_t index = hash % table -> capacity;
    size_t visited = 0;
    HashEntry *first_tombstone = NULL;

    while (visited < table -> capacity){

        HashEntry *const entry = &table -> entries[index];

        if (entry -> state == EMPTY) {

            if (first_tombstone != NULL) {
                return first_tombstone;
            }

            return entry;
        }

        if (entry -> state == OCCUPIED){

            if (hash == entry -> hash){

                if (strcmp(entry -> key, key) == 0) {

                    return entry;
                }
            }
        }

        if (entry -> state == TOMBSTONE && first_tombstone == NULL){
                first_tombstone = entry;
        }

        index = probe_next(index,table -> capacity);
        
        visited ++;
    }

    if (first_tombstone != NULL){

        return first_tombstone;
    }

    return NULL;
}



bool rehash_table(HashTable *table, size_t new_capacity){
    if (table == NULL || new_capacity == 0){
        return false;
    }

    if (table -> entries == NULL){
        return false;
    }

    if (new_capacity < table -> size){
        return false;
    }

    if (new_capacity > SIZE_MAX / sizeof(HashEntry)){ 
        return false;
    }

    HashTable new_hashtable = {0};

    HashEntry *new_entries = malloc(new_capacity * sizeof(HashEntry));

    if (new_entries == NULL){
        return false;
    }

    memset(new_entries, 0, new_capacity * sizeof(HashEntry));

    new_hashtable.entries = new_entries;
    new_hashtable.capacity = new_capacity;
    new_hashtable.size = 0;


    for (size_t i = 0; i < table -> capacity; i++){
        HashEntry *entry = &table -> entries[i];

        if (entry -> state == EMPTY || entry -> state == TOMBSTONE){
            continue;
        }

        HashEntry *new_entry = find_slot(&new_hashtable,entry -> key, entry -> hash);

        if (new_entry == NULL) {
            free(new_entries);
            return false;
        }

        new_entry -> hash = entry -> hash;

        new_entry -> key = entry -> key;

        new_entry -> value = entry -> value;

        new_entry -> state = OCCUPIED;

        new_hashtable.size++;
    }

    if (new_hashtable.size != table -> size){
        free(new_entries);
        return false;
    }

    free(table -> entries);

    table -> entries = new_entries;

    table -> capacity = new_capacity;

    table -> size = new_hashtable.size;

    return true;    
}


