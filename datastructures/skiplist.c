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

SkipList *skiplist_create(void) {
    SkipList *list = malloc(sizeof(SkipList));

    if (list == NULL) {
        return NULL;
    }

    SkipNode *header = malloc(sizeof(SkipNode));

    if (header == NULL) {
        free(list);
        return NULL;
    }

    header->member = NULL;
    header->score = 0;

    for (size_t i = 0; i < SKIPLIST_MAX_LEVEL; i++) {
        header->forward[i] = NULL;
    }

    header->backward=NULL;
    header->level=SKIPLIST_MAX_LEVEL;

    list->header=header;
    list->tail = NULL;
    list->level = 1;
    list->length = 0;

    return list;
}


bool skiplist_insert(SkipList *list, double score, const char *member)
{
    if (list == NULL || member == NULL) {
        return false;
    }

    SkipNode *update[SKIPLIST_MAX_LEVEL];
    SkipNode *current = list->header;

    /* Find insertion position at every active level. */
    for (int i = list->level - 1; i >= 0; i--) {

        while (current->forward[i] != NULL && (current->forward[i]->score < score || (current->forward[i]->score == score && strcmp(current->forward[i]->member, member) < 0))) {

            current = current->forward[i];
        }

        update[i] = current;
    }

    /* Check whether the element already exists. */
    current = current->forward[0];

    if (current != NULL &&
        current->score == score &&
        strcmp(current->member, member) == 0) {
        return false;
    }

    /* Choose a random height for the new node. */
    int level = random_level();

    /* Grow the skip list if necessary. */
    if (level > list->level) {

        for (int i = list->level; i < level; i++) {
            update[i] = list->header;
        }

        list->level = level;
    }

    /* Allocate the new node. */
    SkipNode *node = malloc(sizeof(SkipNode));

    if (node == NULL) {
        return false;
    }

    node->member = strdup(member);

    if (node->member == NULL) {
        free(node);
        return false;
    }

    /* Initialize node fields. */
    node->score = score;
    node->level = level;
    node->backward = NULL;

    for (int i = 0; i < SKIPLIST_MAX_LEVEL; i++) {
        node->forward[i] = NULL;
    }

    /* Insert the node at every level it participates in. */
    for (int i = 0; i < level; i++) {
        node->forward[i] = update[i]->forward[i];
        update[i]->forward[i] = node;
    }

    /* Update backward links. */
    if (update[0] == list->header) {
        node->backward = NULL;
    } else {
        node->backward = update[0];
    }

    if (node->forward[0] != NULL) {
        node->forward[0]->backward = node;
    } else {
        list->tail = node;
    }

    /* Update metadata. */
    list->length++;

    return true;
}


bool skiplist_delete(SkipList *list, double score, const char *member) {
    if (list == NULL || member == NULL) {
        return false;
    }

    if (list->header == NULL) {
        return false;
    }

    SkipNode *update[SKIPLIST_MAX_LEVEL];
    SkipNode *current = list->header;
    int level = list->level - 1;

    for (int i = level; i >= 0; i--) {
        while (current->forward[i] != NULL && (current->forward[i]->score < score || (current->forward[i]->score == score && strcmp(current->forward[i]->member,member) < 0))) {
            current = current->forward[i];
        }

        update[i] = current;
    }

    current = current->forward[0];

    if (current == NULL || current->score != score || strcmp(current->member, member) != 0) {
        return false;
    }

    for (int i = 0; i < current->level; i++) {
        update[i]->forward[i] = current->forward[i];
    }

    if (current->forward[0] != NULL) {
        current->forward[0]->backward = current->backward;
    } else {
        list->tail = current->backward;
    }

    while (list->level > 1 && list->header->forward[list->level - 1] == NULL) {
        list->level--;
    }

    list->length--;

    free(current->member);
    free(current);

    return true;
}

SkipNode *skiplist_search(SkipList *list, double score, const char *member) {
    if (list == NULL || member == NULL) {
        return NULL;
    }

    if (list->header == NULL) {
        return NULL;
    }

    SkipNode *current = list->header;

    for (int level = list->level - 1; level >= 0; level--) {
        while (current->forward[level] != NULL && 
            (current->forward[level]->score < score || 
                (current->forward[level]->score == score && 
                    strcmp(current->forward[level]->member, member) < 0))) {
            current = current->forward[level];
        }
    }

    current = current->forward[0];

    if (current == NULL || current->score != score || strcmp(current->member, member) != 0) {
        return NULL;
    }

    return current;
}

size_t skiplist_range(SkipList *list, double min, double max, SkipNode **result) {
    if (list == NULL || list->header == NULL || result == NULL) {
        return 0;
    }

    if (min > max) {
        return 0;
    }

    free(*result);
    *result = NULL;

    SkipNode *current = list->header;

    for (int level = list->level - 1; level >= 0; level--) {
        while (current->forward[level] != NULL && current->forward[level]->score < min) {
            current = current->forward[level];
        }
    }

    current = current->forward[0];

        
}