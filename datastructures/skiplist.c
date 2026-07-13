#include "../include/common.h"
#include "../include/skiplist.h"


int random_level(void) {
    int level = 1;

    while ((double)rand() / RAND_MAX < SKIPLIST_P) {
        if (level >= SKIPLIST_MAX_LEVEL) {
            break;
        }
        level++;
    }

    return level;
}