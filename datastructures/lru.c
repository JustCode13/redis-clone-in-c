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
    if (db == NULL || object == NULL || object->lru_node != NULL) {
        return;
    }

    ListNode *node = list_push_front(&db->lru, object);

    if (node == NULL) {
        return;
    }

    object->lru_node = node;

    return;
}

void lru_remove(Database *db, RedisObject *object) {
    if (db == NULL || object == NULL || object->lru_node == NULL) {
        return;
    }

    ListNode *node = object->lru_node;

    list_remove(&db->lru, node);

    object->lru_node = NULL;

    return;
}


RedisObject *lru_evict(Database *db) {
    if (db == NULL) {
        return NULL;
    }

    ListNode *node = list_back(&db->lru);

    if (node == NULL || node->data == NULL) {
        return NULL;
    }

    RedisObject *object = (RedisObject *)node->data;

    list_remove(&db->lru, node);

    object->lru_node = NULL;

    return object;
}

RedisObject *lru_oldest(Database *db) {
    if (db == NULL) {
        return NULL;
    }

    ListNode *node = list_back(&db->lru);

    if (node == NULL || node->data == NULL) {
        return NULL;
    }

    return (RedisObject *)node->data;
}