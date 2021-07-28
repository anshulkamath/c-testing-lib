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
    
    // comparator callback function
    int (*comparator) (const void *a, const void* b);
} linked_list_t;

typedef struct ll_iterator {
    list_node_t *curr;
} ll_iterator_t;

// **************************
// **   Helper Functions   **
// **************************

/** Returns a pointer to the ith node in a list  */
static list_node_t* get_ith_node(linked_list_t *list, size_t i) {
    list_node_t *node = list->head;
    while(i--) node = node->next;

    return node;
}

// *****************************
// **   Linked List Methods   **
// *****************************

linked_list_t* create_list(size_t num_bytes) {
    linked_list_t *list = malloc(sizeof(linked_list_t));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    list->num_bytes = num_bytes;
    list->comparator = NULL;
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

void set_comparator(linked_list_t *list, int (*comparator)(const void *a, const void *b)) {
    list->comparator = comparator;
}

int contains(linked_list_t *list, const char *val) {
    list_node_t *curr = list->head;

    while (curr) {
        if (list->comparator ? list->comparator(curr->val, val) : curr->val == val)
            return 1;

        curr = curr->next;
    }

    return 0;
}

void get(linked_list_t *list, size_t index, char *dest) {
    // don't do anything if the index is out of bounds
    if (index >= size(list)) return;

    list_node_t *node = get_ith_node(list, index);

    memcpy(dest, node->val, list->num_bytes);
}

void list_insert(linked_list_t *list, size_t index, const char *val) {
    // don't do anything if the index is out of bounds
    if (index > size(list)) return;

    // if the index is either the beginning or end, pass to push_front/push_back
    if (index == 0) {
        push_front(list, val);
        return;
    } else if (index == size(list)) {
        push_back(list, val);
        return;
    }

    list_node_t *node = get_ith_node(list, index - 1);
    node->next = create_node(val, list->num_bytes, node, node->next);

    ++list->size;
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
