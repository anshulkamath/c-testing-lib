#include "linked-list.h"
#include <string.h>
#include <stdio.h>

// *****************************
// **    List Node Headers    **
// *****************************
typedef struct list_node list_node_t;

static list_node_t* create_node(const char *val, size_t len, list_node_t *prev, list_node_t *next);

static void destroy_node(list_node_t *node);

// ****************************
// **    Type definitions    **
// ****************************


typedef struct list_node {
    list_node_t *next;      // pointer to the next element
    list_node_t *prev;      // pointer to the previous element
    char *val;
} list_node_t;

typedef struct linked_list {
    list_node_t *head;      // pointer to the head of the list
    list_node_t *tail;      // pointer to the tail of the list
    size_t size;            // size of the list
    size_t num_bytes;       // number of bytes for the val
} linked_list_t;

typedef struct ll_iterator {
    list_node_t *curr;
} ll_iterator_t;

// *****************************
// **   Linked List Methods   **
// *****************************

linked_list_t* create_list(size_t num_bytes) {
    linked_list_t *list = malloc(sizeof(linked_list_t));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    list->num_bytes = num_bytes;
    return list;
}

size_t size(linked_list_t *list) {
    return list->size;
}

size_t get_num_bytes(linked_list_t *list) {
    return list->num_bytes;
}

char* get_head(linked_list_t *list) {
    return list->head ? list->head->val : NULL;
}

char* get_tail(linked_list_t *list) {
    return list->tail ? list->tail->val : NULL;
}

void push_front(linked_list_t *list, const char *val) {
    if (!list->size) {
        list->head = create_node(val, list->num_bytes, NULL, NULL);
        list->tail = list->head;
        ++list->size;
        return;
    }

    // create a new node that has the old head as its next element
    // set the new node to be the head of the list
    list->head = create_node(val, list->num_bytes, NULL, list->head);

    // if we had 1 element, then the second element is now the tail
    if (list->size == 1) list->tail = list->head->next;

    ++list->size;
}

void push_back(linked_list_t *list, const char *val) {
    // if the list is empty, handle with push_front
    if (!list->size) {
        push_front(list, val);
        return;
    }

    // add a new node to the end of the list with a copy of the given value
    // then make the new tail point to the new node
    list->tail = list->tail->next = create_node(val, list->num_bytes, list->tail, NULL);

    ++list->size;
}

void pop_front(linked_list_t *list, char *dest) {
    // keep track of old head
    list_node_t *old_head = list->head;
    
    // updating the new head
    list->head = old_head->next;

    // updating tail in edge case
    if (list->size == 1)
        list->tail = list->head;
    else
        list->head->prev = NULL;

    // copy the val of the head into the dest
    memcpy(dest, old_head->val, list->num_bytes);

    //  destroy the old head and decrement from size
    destroy_node(old_head);
    --list->size;
}

void pop_back(linked_list_t *list, char *dest) {
    // keep track of old tail
    list_node_t *old_tail = list->tail;
    
    // updating the new tail
    list->tail = old_tail->prev;

    // updating head in edge case
    if (list->size == 1)
        list->head = list->tail;
    else
        list->tail->next = NULL;

    // copy the val of the head into the dest
    memcpy(dest, old_tail->val, list->num_bytes);

    //  destroy the old head and decrement from size
    destroy_node(old_tail);
    --list->size;
}

void destroy_list(linked_list_t *list) {
    while (list->head) {
        list_node_t *old_head = list->head;
        list->head = list->head->next;
        destroy_node(old_head);
    }

    free(list);
}

// ***************************
// **   List Node Methods   **
// ***************************

list_node_t* create_node(const char *val, size_t len, list_node_t *prev, list_node_t *next) {
    list_node_t *node = malloc(sizeof(list_node_t));
    node->val = malloc(sizeof(*val) * len);
    node->prev = prev;
    node->next = next;
    memcpy(node->val, val, len * sizeof(*val));

    return node;
}

void destroy_node(list_node_t *node) {
    free(node->val);
    free(node);
}

// **************************
// **   Iterator Methods   **
// **************************
