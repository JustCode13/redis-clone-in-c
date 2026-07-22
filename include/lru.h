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


#endif /* LRU_H */