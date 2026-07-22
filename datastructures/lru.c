#include "database.h"
#include "object.h"

void lru_touch(Database *db, RedisObject *object) {
    if (db == NULL || object == NULL || object->lru_node == NULL) {
        return;
    }

    ListNode *node = object->lru_node;

    list_move_front(&db->lru, node);

    return;
}

void lru_insert(Database *db, RedisObject *object) {
    if (db == NULL || object == NULL || object->lru_node == NULL) {
        return;
    }

    
}