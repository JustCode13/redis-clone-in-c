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

        case OBJ_STRING: {
            const char *str = (const char *)object->value;

            if (str != NULL) {
                memory += strlen(str) + 1;
            }

            break;
        }

        case OBJ_LIST: {
            List *list = (List *)object->value;

            if (list != NULL) {
                memory += sizeof(List);

                for (ListNode *node = list->head.next;
                     node != &list->tail;
                     node = node->next) {

                    memory += sizeof(ListNode);

                    /*
                     * If each node owns dynamically allocated data,
                     * count it here.
                     *
                     * Example:
                     *
                     * if (node->data != NULL) {
                     *     memory += object_memory_usage(
                     *         (const RedisObject *)node->data
                     *     );
                     * }
                     */
                }
            }

            break;
        }

        case OBJ_HASH: {
            HashTable *table = (HashTable *)object->value;

            if (table != NULL) {

                memory += sizeof(HashTable);
                memory += table->capacity * sizeof(HashEntry);

                for (size_t i = 0; i < table->capacity; i++) {

                    HashEntry *entry = &table->entries[i];

                    if (entry->state != OCCUPIED) {
                        continue;
                    }

                    if (entry->key != NULL) {
                        memory += strlen(entry->key) + 1;
                    }

                    if (entry->value != NULL) {
                        memory += object_memory_usage(
                            (const RedisObject *)entry->value
                        );
                    }
                }
            }

            break;
        }

        case OBJ_SET: {
            HashTable *table = (HashTable *)object->value;

            if (table != NULL) {

                memory += sizeof(HashTable);
                memory += table->capacity * sizeof(HashEntry);

                for (size_t i = 0; i < table->capacity; i++) {

                    HashEntry *entry = &table->entries[i];

                    if (entry->state != OCCUPIED) {
                        continue;
                    }

                    if (entry->key != NULL) {
                        memory += strlen(entry->key) + 1;
                    }

                    /*
                     * Most Redis-style sets store only keys.
                     * Do not count entry->value unless your
                     * implementation actually allocates an object there.
                     */
                }
            }

            break;
        }

        case OBJ_ZSET: {
            SkipList *list = (SkipList *)object->value;

            if (list != NULL) {

                memory += sizeof(SkipList);

                SkipNode *current = list->header->forward[0];

                while (current != NULL) {

                    memory += sizeof(SkipNode);

                    if (current->member != NULL) {
                        memory += strlen(current->member) + 1;
                    }

                    /*
                     * If SkipNode dynamically allocates its
                     * forward pointer array, count it here.
                     *
                     * Example:
                     * memory += current->level * sizeof(SkipNode *);
                     */

                    current = current->forward[0];
                }
            }

            break;
        }

        default:
            break;
    }

    return memory;
}