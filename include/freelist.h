#ifndef FREELIST_H
#define FREELIST_H

#include <stddef.h>

typedef struct FreeBlock
{
    size_t size;

    struct FreeBlock *next;

} FreeBlock;

/* Allocation */

void *freelist_alloc(FreeBlock **free_list,
                     size_t size);

/* Free Memory */

void freelist_free(FreeBlock **free_list,
                   void *ptr,
                   size_t size);

/* Merge Adjacent Free Blocks */

void freelist_merge(FreeBlock **free_list);

#endif