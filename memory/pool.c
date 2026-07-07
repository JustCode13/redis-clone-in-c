#include "../include/common.h"
#include "../include/allocator.h"

PoolAllocator *pool_create(size_t object_size, size_t object_count, size_t alignment){
    if (object_size < 1 || object_count < 1) {
        return NULL;
    }

    if (alignment == 0){
        return NULL;
    }

    if ((alignment & (alignment -1)) != 0) {
        return NULL;
    }

    PoolAllocator *pool = malloc(sizeof(PoolAllocator));

    if (pool == NULL){
        return NULL;
    }

    if (object_size > SIZE_MAX - (alignment - 1)) {
        free(pool);
        return NULL;
    }
        
    size_t aligned_object_size = (object_size + alignment - 1) & ~(alignment - 1);

    if (object_count > SIZE_MAX / aligned_object_size){
        free(pool);
        return NULL;
    }

    size_t total_size = aligned_object_size * object_count;

    void *memory = malloc(total_size);

    if (memory == NULL){
        free(pool);
        return NULL;
    }

    u8 *base = memory;

    for (size_t i = 0; i < object_count; i++){

        FreeBlock *block = (base + i * aligned_object_size);

        block->size = aligned_object_size;

        if (i == object_count -1){
            block -> next = NULL;
        } else {
            block -> next = (FreeBlock *)(base + (i + 1) * aligned_object_size);
        }
    }

    FreeBlock *free_block = malloc(object_count * sizeof(aligned_object_size));

    pool -> memory = memory;
    pool -> free_list = (FreeBlock *)memory;
    pool -> object_size = aligned_object_size;
    pool -> object_count = object_count;
    pool -> alignment = alignment;
    
    return pool;
}

