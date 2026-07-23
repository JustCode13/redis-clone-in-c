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

    if (now == (time_t) - 1) {
        return;
    }

    u64 current_time = (u64)now;
}