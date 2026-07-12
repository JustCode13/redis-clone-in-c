#ifndef HASH_H               // Prevents this header file from being included more than once
#define HASH_H

#include "common.h"          // Common types, macros, and enums used throughout the project
#include "allocator.h"       // Custom memory allocation functions


// Represents the current state of a slot in the hash table
typedef enum {

    // Slot has never been used
    EMPTY,

    // Slot currently contains a valid key-value pair
    OCCUPIED,

    // Slot previously contained data but was deleted
    TOMBSTONE

} EntryState;


// Represents one entry (one key-value pair) inside the hash table
typedef struct HashEntry {

    // Pointer to the key string
    char *key;

    // Pointer to the value associated with the key
    void *value;

    // Cached hash value of the key to avoid recomputing it
    u64 hash;

    // Current state of this entry (EMPTY, OCCUPIED, or TOMBSTONE)
    EntryState state;

} HashEntry;


// Represents the entire hash table
typedef struct HashTable {

    // Array of hash table entries
    HashEntry *entries;

    // Total number of slots currently allocated
    size_t capacity;

    // Number of valid key-value pairs currently stored
    size_t size;

    // Number of deleted slots marked as TOMBSTONE
    size_t tombstones;

    // Maximum load factor before resizing the table
    float load_factor;

} HashTable;

u64 fnv1a_hash(const char *key);

u64 djb2_hash(const char *key);

// Creates a new hash table with the specified initial capacity
HashTable *hash_create(size_t capacity);


// Inserts a new key-value pair into the hash table
// Returns true if insertion succeeds, otherwise false
bool hash_insert(
    HashTable *table,
    const char *key,
    void *value
);


// Searches for a key and returns its associated value
// Returns NULL if the key does not exist
void *hash_find(
    HashTable *table,
    const char *key
);


// Removes a key-value pair from the hash table
// Returns true if the key was removed, otherwise false
bool hash_remove(
    HashTable *table,
    const char *key
);


// Changes the capacity of the hash table and rehashes all entries
// Returns true if resizing succeeds, otherwise false
bool hash_resize(
    HashTable *table,
    size_t new_capacity
);


// Frees all memory used by the hash table
void hash_destroy(HashTable *table);

#endif     // End of include guard