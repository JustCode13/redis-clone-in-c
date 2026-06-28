#ifndef OBJECT_H                 // Prevents this header file from being included multiple times
#define OBJECT_H

#include "common.h"              // Common types, macros, and utility definitions
#include "list.h"                // Linked list implementation
#include "hash.h"                // Hash table implementation
#include "skiplist.h"            // Skip list implementation


// Represents the kind of value stored inside a Redis object
typedef enum {

    // Object stores a string
    OBJ_STRING,

    // Object stores a list
    OBJ_LIST,

    // Object stores a hash table
    OBJ_HASH,

    // Object stores a set
    OBJ_SET,

    // Object stores a sorted set
    OBJ_ZSET

} RedisObjectType;


// Represents a Redis value stored in the database
typedef struct RedisObject {

    // Specifies what type of object this is
    RedisObjectType type;

    // Points to the actual data
    // Its real type depends on the value of 'type'
    //
    // OBJ_STRING -> char *
    // OBJ_LIST   -> List *
    // OBJ_HASH   -> HashTable *
    // OBJ_SET    -> HashTable *
    // OBJ_ZSET   -> SkipList *
    void *value;

    // Expiration time in Unix timestamp
    // 0 usually means the object never expires
    u64 expire_at;

    // Number of references pointing to this object
    // Used for reference counting
    u32 refcount;

    // Pointer to this object's node inside the LRU list
    // Used for cache eviction algorithms
    ListNode *lru_node;

} RedisObject;


// Creates a Redis string object
// Returns the newly created object
RedisObject *object_create_string(const char *value);


// Creates an empty Redis list object
// Returns the newly created object
RedisObject *object_create_list(void);


// Creates an empty Redis hash object
// Returns the newly created object
RedisObject *object_create_hash(void);


// Creates an empty Redis set object
// Returns the newly created object
RedisObject *object_create_set(void);


// Creates an empty Redis sorted set object
// Returns the newly created object
RedisObject *object_create_zset(void);


// Increases the object's reference count by one
void object_retain(RedisObject *obj);


// Decreases the object's reference count
// Automatically destroys the object if the count reaches zero
void object_release(RedisObject *obj);


// Frees all memory used by the object
void object_destroy(RedisObject *obj);

#endif      // End of include guard