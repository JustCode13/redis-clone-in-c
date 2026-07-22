#ifndef LRU_H
#define LRU_H

#include "common.h"
#include "database.h"
#include "object.h"


// Marks an object as recently used by moving it
// to the front of the LRU list.
void db_touch_lru(
    Database *db,
    RedisObject *obj
);


// Removes the least recently used object from the database.
//
// Returns true if an object was evicted,
// otherwise false.
bool db_evict_lru(
    Database *db
);


#endif /* LRU_H */