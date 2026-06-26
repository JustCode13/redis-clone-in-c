#ifndef SKIPLIST_H
#define SKIPLIST_H

#include <stddef.h>
#include <stdbool.h>

#define SKIPLIST_MAX_LEVEL 16

typedef struct SkipNode
{
    double score;

    char *member;

    struct SkipNode *forward[SKIPLIST_MAX_LEVEL];

} SkipNode;

typedef struct
{
    SkipNode *header;

    int level;

    size_t length;

} SkipList;

/* Creation / Destruction */

SkipList *skiplist_create(void);

void skiplist_destroy(SkipList *list);

/* Operations */

int skiplist_insert(SkipList *list,
                    double score,
                    const char *member);

int skiplist_delete(SkipList *list,
                    double score,
                    const char *member);

SkipNode *skiplist_search(SkipList *list,
                          double score,
                          const char *member);

size_t skiplist_rank(SkipList *list,
                     double score,
                     const char *member);

#endif