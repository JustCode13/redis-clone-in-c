#ifndef LIST_H        // Prevents this header file from being included multiple times
#define LIST_H

#include "common.h"   // Includes common types, macros, and shared definitions

// Represents a single node in the doubly linked list
typedef struct ListNode {

    // Points to the previous node
    struct ListNode *prev;

    // Points to the next node
    struct ListNode *next;

    // Stores a pointer to any type of data
    void *data;

} ListNode;


// Represents the complete doubly linked list
typedef struct List {

    // Dummy head node used to simplify insert and remove operations
    ListNode head;

    // Dummy tail node used to simplify insert and remove operations
    ListNode tail;

    // Stores the current number of data nodes in the list
    size_t size;

} List;


// Initializes an empty linked list
void list_init(List *list);


// Inserts a new node at the beginning of the list
// Returns a pointer to the newly created node
ListNode *list_push_front(
    List *list,
    void *data
);


// Inserts a new node at the end of the list
// Returns a pointer to the newly created node
ListNode *list_push_back(
    List *list,
    void *data
);


// Removes a node from the list
void list_remove(
    List *list,
    ListNode *node
);


// Moves an existing node to the front of the list
void list_move_front(
    List *list,
    ListNode *node
);


// Returns the first data node in the list
ListNode *list_front(List *list);


// Returns the last data node in the list
ListNode *list_back(List *list);


// Returns true if the list has no data nodes, otherwise false
bool list_empty(List *list);


// Removes all nodes from the list and resets it to an empty state
void list_clear(List *list);

#endif      // End of include guard