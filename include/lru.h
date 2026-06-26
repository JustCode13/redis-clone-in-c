#ifndef LRU_H
#define LRU_H

#include <stddef.h>

typedef struct LRUNode
{
    char *key;

    struct LRUNode *prev;

    struct LRUNode *next;

} LRUNode;

typedef struct
{
    LRUNode head;

    LRUNode tail;

    size_t count;

} LRUCache;

/* Initialization / Cleanup */

void lru_init(LRUCache *cache);

void lru_destroy(LRUCache *cache);

/* Operations */

void lru_touch(LRUCache *cache,
               LRUNode *node);

LRUNode *lru_insert(LRUCache *cache,
                    const char *key);

void lru_remove(LRUCache *cache,
                LRUNode *node);

LRUNode *lru_evict(LRUCache *cache);

#endif