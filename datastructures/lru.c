#include "database.h"
#include "object.h"

void lru_touch(Database *db, RedisObject *object) {
    if (db == NULL || object == NULL || object->lru_node == NULL) {
        return;
    }

    
}