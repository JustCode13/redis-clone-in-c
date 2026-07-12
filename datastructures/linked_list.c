#include "../include/common.h"
#include "../include/list.h"


void list_init(List *list) {
    if (list == NULL ) {
        return;
    }

    list->head.prev = NULL;
    list->head.next = &list->tail;
    
    list->tail.prev = &list->head;
    list->tail.next = NULL;
    
    list->size = 0;
}

ListNode *list_push_front(List *list, void *data) {
    if (list == NULL) {
        return NULL;
    }

    ListNode *node = malloc(sizeof(*node));

    if (node == NULL) {
        return NULL;
    }

    node->data = data;
    node->prev = &list->head;
    node->next = list->head.next;

    list->head.next->prev = node;
    list->head.next = node;
    list->size++;
    
    return node;
}


ListNode *list_push_back(List *list, void *data) {
    if (list == NULL) {
        return NULL;
    }

    ListNode *node = malloc(sizeof(*node));

    if (node == NULL) {
        return NULL;
    }

    node->data = data;
    node->prev = list->tail.prev;
    node->next = &list->tail;

    list->tail.prev->next = node;
    list->tail.prev = node;
    list->size++;
    
    return node;
}

void list_remove(List *list, ListNode *node) {
    if (list == NULL || node == NULL) {
        return;
    }

    if (node == &list->head || node == &list->tail)  {
        return;
    }

    ListNode *prev_node = node->prev;
    ListNode *next_node = node->next;

    prev_node->next = next_node;
    next_node->prev = prev_node;

    node->prev = NULL;
    node->next = NULL;
    node->data = NULL;

    list->size--;

    free(node);
}

