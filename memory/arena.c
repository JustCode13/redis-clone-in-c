#include "../include/commands.h"
#include "../include/common.h"


// Creates a new memory arena with the specified capacity
Arena *arena_create(size_t capacity)
{
    // Allocate memory for the Arena structure itself
    Arena *arena = malloc(sizeof(*arena));

    // Check if allocating the Arena structure failed
    if (arena == NULL) {
        return NULL;
    }

    // Allocate the large block of memory that the arena will manage
    void *memory = malloc(capacity);

    // If allocating the memory block failed
    if (memory == NULL) {

        // Free the already allocated Arena structure to avoid a memory leak
        free(arena);

        // Return NULL to indicate failure
        return NULL;
    }

    // Store the pointer to the allocated memory block
    arena->memory = memory;

    // Store the total size of the memory block
    arena->capacity = capacity;

    // No memory has been used yet, so start at offset 0
    arena->offset = 0;

    // Return the initialized arena
    return arena;
}


