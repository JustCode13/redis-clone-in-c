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

