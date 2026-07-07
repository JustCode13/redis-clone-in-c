#include "../include/memory.h"

static MemoryStats memory_stats;

void *align_pointer(void *ptr, size_t alignment) {
    if (ptr == NULL || alignment == 0){
        return NULL;
    }

    if ((alignment & (alignment -1)) != 0){
        return NULL;
    }

    uptr_t int_ptr = (uptr_t)ptr;

    uptr_t aligned = (int_ptr + alignment - 1) & ~(alignment - 1);

    void *aligned_ptr = (void *)aligned;

    return aligned_ptr;
}

void *checked_malloc(size_t size) {
    if (size == 0){
        return NULL;
    };

    void *memory = malloc(size);

    if (memory == NULL){
        return NULL;
    }

    memory_stats.total_allocations ++;
    memory_stats.bytes_allocated += size;
    memory_stats.current_memory_usage += size;
    if (memory_stats.peak_memory_usage < size){
        memory_stats.peak_memory_usage += size;
    }

    return memory;
}
