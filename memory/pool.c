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
        goto cleanup;
    }
        
    size_t aligned_object_size = (object_size + alignment - 1) & ~(alignment - 1);

    if (object_count > SIZE_MAX / aligned_object_size){
        goto cleanup;
    }

    size_t total_size = aligned_object_size * object_count;

    void *memory = malloc(total_size);

    if (memory == NULL){
        goto cleanup;
    }

    u8 *base = (u8 *)memory;

    for (size_t i = 0; i < object_count; i++){

        FreeBlock *block = (FreeBlock *)(base + i * aligned_object_size);

        block->size = aligned_object_size;

        if (i == object_count -1){
            block -> next = NULL;
        } else {
            u8 *next_address = base + ( i + 1) * aligned_object_size;
            block -> next = (FreeBlock *)next_address;
        }
    }

    pool -> memory = memory;
    pool -> free_list = (FreeBlock *)memory;
    pool -> object_size = aligned_object_size;
    pool -> object_count = object_count;
    pool -> alignment = alignment;
    
    return pool;


    cleanup:
    free(pool);
    return NULL;
}


void *pool_alloc(PoolAllocator *pool){
    if (pool == NULL){
        fprintf(stderr, "No free client objects available\n");
        return NULL;    
    }

    if (pool -> free_list == NULL) {
        return NULL;
    }

    FreeBlock *block = pool -> free_list;

    pool -> free_list = block -> next;

    return (void *)block;
}