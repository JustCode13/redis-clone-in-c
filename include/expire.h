#ifndef EXPIRE_H
#define EXPIRE_H

#include "common.h"
#include "database.h"
#include "object.h"


// Sets an expiration time for a key.
// expire_at is an absolute monotonic timestamp.
// Returns true if the expiration was set successfully.
bool db_expire(
    Database *db,
    const char *key,
    u64 expire_at
);


// Removes all expired keys from the database.
void db_cleanup_expired(
    Database *db
);


// Returns the remaining time-to-live (TTL) in milliseconds.
//
// Return values:
//   > 0 : Remaining TTL
//   = 0 : Expired
//   < 0 : No expiration set
i64 ttl_remaining(
    const RedisObject *obj
);


// Returns the current monotonic time in milliseconds.
u64 current_monotonic_time(void);


#endif /* EXPIRE_H */