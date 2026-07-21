#ifndef SKIPLIST_H                 // Prevents this header file from being included multiple times
#define SKIPLIST_H

#include "common.h"                // Includes common project definitions, types, and macros
#include <stdlib.h>                // Provides memory allocation functions like malloc() and free()
#include <math.h>                  // Provides mathematical functions if needed by the skip list

// Maximum number of levels a node can have
#define SKIPLIST_MAX_LEVEL 16

// Probability used when deciding whether a node gets promoted to the next level
#define SKIPLIST_P 0.25


// Represents a single node inside the skip list
typedef struct SkipNode {

    // String value stored in the node
    char *member;

    // Score used to keep the skip list sorted
    double score;

    // Array of forward pointers, one for each level
    struct SkipNode *forward[SKIPLIST_MAX_LEVEL]; // pointer to node ahead of it on each level

    // Pointer to the previous node on the lowest level
    struct SkipNode *backward;

    // Highest level this node exists on
    int level;

} SkipNode;


// Represents the entire skip list
typedef struct SkipList {

    // First node of the skip list (dummy header node)
    SkipNode *header;

    // Last node in the skip list
    SkipNode *tail;

    // Current highest level being used in the skip list
    int level;

    // Total number of elements stored in the skip list
    size_t length;

} SkipList;


// Creates and initializes a new empty skip list
SkipList *skiplist_create(void);


// Inserts a new member with the given score into the skip list
// Returns true if insertion succeeds, otherwise false
bool skiplist_insert(
    SkipList *list,
    double score,
    const char *member
);


// Deletes the specified member from the skip list
// Returns true if deletion succeeds, otherwise false
bool skiplist_delete(
    SkipList *list,
    double score,
    const char *member
);


// Searches for a member with the given score
// Returns a pointer to the node if found, otherwise NULL
SkipNode *skiplist_search(
    SkipList *list,
    double score,
    const char *member
);


// Returns all nodes whose scores are between min and max
// Stores matching nodes into the result array
// Returns the number of matching nodes found
size_t skiplist_range(
    SkipList *list,
    double min,
    double max,
    SkipNode **result
);


// Frees all memory used by the skip list
void skiplist_destroy(SkipList *list);

#endif      // End of include guard