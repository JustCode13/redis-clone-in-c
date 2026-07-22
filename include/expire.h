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



#endif /* EXPIRE_H */