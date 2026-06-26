#ifndef OBJECT_H
#define OBJECT_H

#include <stdint.h>
#include <stddef.h>

#include "common.h"
#include "lru.h"

/* Forward Declarations */

typedef struct StringObject StringObject;
typedef struct ListObject ListObject;
typedef struct HashObject HashObject;
typedef struct SetObject SetObject;
typedef struct ZSetObject ZSetObject;

/* Object Types */

typedef enum
{
    OBJ_STRING,
    OBJ_LIST,
    OBJ_HASH,
    OBJ_SET,
    OBJ_ZSET

} ObjectType;

/* Generic Redis Object */

typedef struct
{
    ObjectType type;

    uint64_t ttl;

    LRUNode *lru_node;

    union
    {
        StringObject *string;

        ListObject *list;

        HashObject *hash;

        SetObject *set;

        ZSetObject *zset;

    } data;

} RedisObject;

#endif