#ifndef ALLOCATOR_H          // Prevents this header file from being included more than once
#define ALLOCATOR_H

#include "common.h"          // Includes common types, macros, and shared definitions

// Represents an arena allocator that allocates memory sequentially
typedef struct Arena {

    // Pointer to the beginning of the allocated memory block
    u8 *memory;

    // Total size of the arena in bytes
    size_t capacity;

    // Current position where the next allocation will be made
    size_t offset;

    // Memory alignment used for allocations
    size_t alignment;

} Arena;


// Represents one free block inside a pool allocator
typedef struct FreeBlock {

    // Size of this free block
    size_t size;  // later check is size even necessary

    // Pointer to the next free block in the free list
    struct FreeBlock *next;

} FreeBlock;


// Represents a pool allocator used for allocating fixed-size objects->client objects
typedef struct PoolAllocator {

    // Pointer to the beginning of the pool memory
    void *memory;

    // Pointer to the first available free block
    FreeBlock *free_list;

    // Size of each object stored in the pool
    size_t object_size;

    // Total number of objects the pool can hold
    size_t object_count;

    // Memory alignment used for objects
    size_t alignment;

} PoolAllocator;


// Creates a new arena allocator with the specified capacity
Arena *arena_create(size_t capacity);


// Allocates a block of memory from the arena
// size = number of bytes to allocate
// alignment = required memory alignment
void *arena_alloc(
    Arena *arena,
    size_t size,
    size_t alignment
);


// Resets the arena so all previous allocations become available again
void arena_reset(Arena *arena);


// Releases all memory used by the arena and destroys it
void arena_destroy(Arena *arena);


// Creates a pool allocator
// object_size = size of each object
// object_count = total number of objects in the pool
PoolAllocator *pool_create(
    size_t object_size,
    size_t object_count,
    size_t alignment
);


// Allocates one object from the pool
void *pool_alloc(PoolAllocator *pool);


// Returns an allocated object back to the pool
void pool_free(
    PoolAllocator *pool,
    void *ptr
);


// Releases all memory used by the pool allocator and destroys it
void pool_destroy(PoolAllocator *pool);

#endif      // End of include guard