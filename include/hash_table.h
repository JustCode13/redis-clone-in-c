#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "common.h"
#include "object.h"

typedef enum
{
    EMPTY,
    OCCUPIED,
    TOMBSTONE

} SlotState;

typedef struct
{
    char *key;

    RedisObject *value;

    SlotState state;

} HashEntry;

typedef struct
{
    HashEntry *entries;

    size_t capacity;

    size_t count;

    size_t tombstones;

} HashTable;

// Creation / Destruction 

HashTable *hash_create(size_t initial_capacity);

void hash_destroy(HashTable *table);

// Basic Operations 

int hash_insert(HashTable *table,
                const char *key,
                RedisObject *value);

RedisObject *hash_find(HashTable *table,
                       const char *key);

int hash_delete(HashTable *table,
                const char *key);

// Internal Operations

int hash_rehash(HashTable *table,
                size_t new_capacity);

// Hash Functions 

uint32_t hash_fnv1a(const char *key);

uint32_t hash_djb2(const char *key);

#endif