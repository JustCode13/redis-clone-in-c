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

SkipNode *create_node(double score, const char *member, int level) {
    if (level < 1 || level > SKIPLIST_MAX_LEVEL || member == NULL) {
        return NULL;
    }

    SkipNode *node = malloc(sizeof(SkipNode));

    if (node == NULL) {
        return NULL;
    }

    char *member_copy = strdup(member);

    if (member_copy == NULL) {
        free(node);
        return NULL;
    }

    node->score = score;
    node->member = member_copy;
    node->level = level;

    for (size_t i = 0; i < SKIPLIST_MAX_LEVEL; i++) {
        node->forward[i] = NULL;
    }

    node->backward=NULL;

    return node;
}