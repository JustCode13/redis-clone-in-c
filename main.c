#include <stdio.h>
#include <stdlib.h>
#include "include/common.h"
#include "include/allocator.h"
#include "include/hash.h"

int main(void){
    u64 hash = fnv1a_hash("shitt");
    u64 hash2 = djb2_hash("shitt");

    printf("Hash Value (FNV-1a): %lu\n", hash);
    printf("Hash Value (DJB2): %lu\n", hash2);

    return 0;
}