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