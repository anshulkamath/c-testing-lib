#include "tester-list.h"
#include <string.h>
#include <stdio.h>

// *****************************
// **    List Node Headers    **
// *****************************
typedef struct tlist_node tlist_node_t;

static tlist_node_t* create_node(const char *val, size_t len, tlist_node_t *prev, tlist_node_t *next);

static void destroy_node(tlist_node_t *node);

// ****************************
// **    Type definitions    **
// ****************************

typedef struct tlist_node {
    tlist_node_t *next;      // pointer to the next element
    tlist_node_t *prev;      // pointer to the previous element
    char *val;
} tlist_node_t;

typedef struct tester_list {
    tlist_node_t *head;      // pointer to the head of the list
    tlist_node_t *tail;      // pointer to the tail of the list
    size_t size;            // size of the list
    size_t num_bytes;       // number of bytes for the val
    
    // comparator callback function
    int (*comparator) (const void *, const void *);
} tester_list_t;

typedef struct tl_iterator {
    tlist_node_t *curr;      // the current value the iterator points to
    size_t num_bytes;       // the number of bytes to store the value
} tl_iterator_t;

// *****************************
// **   Linked List Methods   **
// *****************************

tester_list_t* t_create_list(size_t num_bytes) {
    tester_list_t *list = malloc(sizeof(tester_list_t));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    list->num_bytes = num_bytes;
    list->comparator = NULL;
    return list;
}

size_t t_size(tester_list_t *list) {
    return list->size;
}

char* t_get_head(tester_list_t *list) {
    return list->head ? list->head->val : NULL;
}

char* t_get_tail(tester_list_t *list) {
    return list->tail ? list->tail->val : NULL;
}

void t_push_back(tester_list_t *list, const char *insertee) {
    // preventing global buffer overflow
    char val[list->num_bytes];
    memset(val, 0, list->num_bytes);
    strcpy(val, insertee);
    
    if (!list->size) {
        list->head = create_node(val, list->num_bytes, NULL, NULL);
        list->tail = list->head;
        ++list->size;
        return;
    }

    // add a new node to the end of the list with a copy of the given value
    // then make the new tail point to the new node
    list->tail = list->tail->next = create_node(val, list->num_bytes, list->tail, NULL);

    ++list->size;
}

void t_destroy_list(tester_list_t *list) {
    while (list->head) {
        tlist_node_t *old_head = list->head;
        list->head = list->head->next;
        destroy_node(old_head);
    }

    free(list);
}

// ***************************
// **   List Node Methods   **
// ***************************

tlist_node_t* create_node(const char *val, size_t len, tlist_node_t *prev, tlist_node_t *next) {
    tlist_node_t *node = malloc(sizeof(tlist_node_t));
    node->val = malloc(sizeof(*val) * len);
    node->prev = prev;
    node->next = next;
    memcpy(node->val, val, len * sizeof(*val));

    return node;
}

void destroy_node(tlist_node_t *node) {
    free(node->val);
    free(node);
}

// **************************
// **   Iterator Methods   **
// **************************

tl_iterator_t* t_create_iterator(tester_list_t *list) {
    tl_iterator_t *iter = malloc(sizeof(tl_iterator_t));
    iter->curr = list->head;
    iter->num_bytes = list->num_bytes;

    return iter;
}

void t_peek(tl_iterator_t *iter, char *dest) {
    memcpy(dest, iter->curr->val, iter->num_bytes);
}

int t_next(tl_iterator_t *iter) {
    iter->curr = iter->curr->next;

    if (!iter->curr) {
        t_destroy_iterator(iter);
        return 0;
    }

    return 1;
}

void t_sprint_list(tester_list_t *list, char *dest) {
    tl_iterator_t *iter = t_create_iterator(list);
    memset(dest, 0, list->size * list->num_bytes);
    strcat(dest, iter->curr->val);

    // destroys iterator for us
    while(t_next(iter)) {
        strcat(dest, " ");
        strcat(dest, iter->curr->val);
    }
}

void t_destroy_iterator(tl_iterator_t *iter) {
    free(iter);
}
