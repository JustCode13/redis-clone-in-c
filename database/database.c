#include "database.h" 
#include "hash.h"
#include "object.h"
#include "list.h"
#include "allocator.h"


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
            
        }
    }
}