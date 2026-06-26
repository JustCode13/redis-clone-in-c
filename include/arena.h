#ifndef ARENA_H
#define ARENA_H

#include <stddef.h>
#include <stdint.h>

#include "common.h"

typedef struct
{
    uint8_t *memory;

    size_t capacity;

    size_t offset;

} Arena;

/* Creation / Destruction */

Arena *arena_create(size_t capacity);

void arena_destroy(Arena *arena);

/* Allocation */

void *arena_alloc(Arena *arena,
                  size_t size,
                  size_t alignment);

/* Reset */

void arena_reset(Arena *arena);

#endif