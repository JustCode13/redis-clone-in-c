#include "database.h" 
#include "hash.h"
#include "object.h"
#include "list.h"
#include "allocator.h"


void update_memory_usage(Database *db, ssize_t delta);
size_t object_memory_usage(const RedisObject *object);


void remove_expired(Database *db) {
    if (db == NULL) {
        return;
    }

    if (db->dict == NULL) {
        return;
    }

    time_t now = time(NULL);

    if (now == (time_t)-1) {
        return;
    }

    u64 current_time = (u64)now;

    for (size_t i = 0; i < db->dict->capacity; i++){
        HashEntry *entry = &db->dict->entries[i];

        if (entry->state == EMPTY || entry->state == TOMBSTONE) {
            continue;
        }

        RedisObject *object = entry->value;

        if (object->expire_at == 0) {
            continue;
        }

        if (object->expire_at <= current_time) {
            if (!hash_remove(db->dict, entry->key)){
                return;
            }

            if (object->lru_node != NULL) {
                list_remove(&db->lru,object->lru_node);
            }

            object_destroy(object);

            db->key_count--;

            // update_memory_usage(db, )
        }
    }
}

size_t object_memory_usage(const RedisObject *object) {
    if (object == NULL) {
        return 0;
    }

    size_t memory = sizeof(RedisObject);

    switch (object->type) {
        case OBJ_STRING: 
            const char *str = object->value;

            if (str != NULL) {
                memory += strlen(str) + 1;
            }

            break;
        
    }
}