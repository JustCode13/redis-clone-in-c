#ifndef MEMORY_H
#define MEMORY_H

#include "common.h"

typedef struct MemoryStats {

    size_t total_allocations;

    size_t total_frees;

    size_t bytes_allocated;

    size_t bytes_freed;

    size_t current_memory_usage;

    size_t peak_memory_usage;

} MemoryStats;

void *align_pointer(void *ptr, size_t alignment);

void *checked_malloc(size_t size);

void *checked_realloc(void *ptr, size_t old_size ,size_t new_size);

void checked_free(void *ptr, size_t size);

MemoryStats memory_statistics(void);

#endif // !MEMORY_H