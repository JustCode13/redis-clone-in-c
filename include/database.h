#ifndef DATABASE_H                 // Prevents this header file from being included multiple times
#define DATABASE_H

#include "common.h"                // Common types, macros, enums, and project-wide definitions
#include "hash.h"                  // Hash table used to store key-value pairs
#include "list.h"                  // Doubly linked list used for the LRU cache
#include "object.h"                // RedisObject definition
#include "allocator.h"             // Memory arena allocator


// Represents the entire Redis database
typedef struct Database {

    // Hash table that stores all key-value pairs
    HashTable *dict;

    // LRU (Least Recently Used) list used for memory eviction
    List lru;

    // Maximum amount of memory the database is allowed to use
    size_t max_memory;

    // Current amount of memory being used
    size_t used_memory;

    // Memory arena used for allocating database objects
    Arena *arena;

    // Total number of keys currently stored
    u64 key_count;

} Database;


// Creates and initializes a new database
// max_memory specifies the maximum memory the database may use
Database *db_create(size_t max_memory);


// Inserts a new key-value pair or updates an existing one
// Returns true if the operation succeeds, otherwise false
bool db_set(
    Database *db,
    const char *key,
    RedisObject *obj
);


// Retrieves the object associated with the given key
// Returns the object if found, otherwise NULL
RedisObject *db_get(
    Database *db,
    const char *key
);


// Deletes the specified key from the database
// Returns true if the key was deleted, otherwise false
bool db_delete(
    Database *db,
    const char *key
);


// Checks whether a key exists in the database
// Returns true if the key exists, otherwise false
bool db_exists(
    Database *db,
    const char *key
);


// Sets an expiration time for a key
// expire_at is the absolute expiration timestamp
// Returns true if successful, otherwise false
bool db_expire(
    Database *db,
    const char *key,
    u64 expire_at
);


// Marks an object as recently used by updating its position in the LRU list
void db_touch_lru(
    Database *db,
    RedisObject *obj
);


// Removes the least recently used object to free memory
// Returns true if an object was evicted, otherwise false
bool db_evict_lru(Database *db);


// Removes all keys whose expiration time has passed
void db_cleanup_expired(Database *db);


// Frees all memory used by the database
void db_destroy(Database *db);

#endif      // End of include guard