#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdlib.h>

typedef struct linked_list linked_list_t;
typedef struct ll_iterator ll_iterator_t;

/**
 * @brief Create a list object
 * 
 * @param num_bytes The number of bytes allocated for each list entry
 * @return linked_list_t* The object that was created
 */
linked_list_t* create_list(size_t num_bytes);

/**
 * @brief Returns the size of a given list
 * 
 * @param list The list which we get the size of
 * @return size_t The size of the list
 */
size_t size(linked_list_t *list);

/**
 * @brief Get the num bytes of each entry in the list
 * 
 * @param list The list to get the num_bytes of
 * @return size_t The number of bytes per entry in the list
 */
size_t get_num_bytes(linked_list_t *list);

/**
 * @brief Get the head of the list
 * 
 * @param list The list to get the head of
 * @return char* A pointer to the head of the list
 */
char* get_head(linked_list_t *list);

/**
 * @brief Get the tail of the list
 * 
 * @param list The list to get the tail of
 * @return char* A pointer to the tail of the list
 */
char* get_tail(linked_list_t *list);

/**
 * @brief Append an element to the front of a list object
 * 
 * @param list The list to which we append
 * @param val The value that is appended
 */
void push_front(linked_list_t *list, const char *val);

/**
 * @brief Append an element to the back of a list object
 * 
 * @param list The list object to which we append
 * @param val The value that is appended
 */
void push_back(linked_list_t *list, const char *val);

/**
 * @brief Pops an element off the front of a list and put it in dest
 * 
 * @param list The list from which we pop
 * @param dest Where to store the popped element
 */
void pop_front(linked_list_t *list, char *dest);

/**
 * @brief Pops an element off the back of a list and put it in dest
 * 
 * @param list The list from which we pop
 * @param dest Where to store the popped element
 */
void pop_back(linked_list_t *list, char *dest);

/**
 * @brief Returns 1 or 0 if the given element is in the list of not
 * 
 * @param list The list which we search
 * @param val The value which we search for
 * @return int Either 1 (if the element is in the list) or 0 (if not)
 */
int contains(linked_list_t *list, const char *val);

/**
 * @brief Returns the element at the given index of a list
 * 
 * @param list The list to get the element from
 * @param index The index of the element to get
 * @param dest The place to store the element that we get
 */
void get(linked_list_t *list, size_t index, char *dest);

/**
 * @brief Inersts an element into the linked list at the given index
 * 
 * @param list The list which we insert into
 * @param val The value to insert into the list
 * @param index The index to which we insert
 */
void list_insert(linked_list_t *list, char *val, size_t index);

/**
 * @brief Deletes an element at the given index from the linked list
 * 
 * @param list The list which we delete from
 * @param index The index of the element to delete
 * @param dest A pointer to store the data that was deleted
 */
void list_delete(linked_list_t *list, size_t index, char *dest);

/**
 * @brief Create a iterator object
 * 
 * @param list The list over which to iterate
 * @return ll_iterator_t* A pointer to the iterator object that was created
 */
ll_iterator_t* create_iterator(linked_list_t *list);

/**
 * @brief Returns 1 if the iterator is not at the end of the list
 * 
 * @param iterator The iterator to check
 * @return int 1 if the iterator is not at the end of the list, else 0
 */
int has_next(ll_iterator_t *iterator);

/**
 * @brief Writes the value of which the iterator is currently pointing to dest
 * 
 * @param iterator The iterator to peek into
 * @param dest Where to put the data
 */
void peek(ll_iterator_t *iterator, char *dest);

/**
 * @brief Advances the iterator to the next element. If the iterator is at the
 *        end of the list, then the iterator will free itself and return 0.
 *        
 * @param iterator The iterator to advance
 * @return int Returns 0 if the iterator has been exhausted. Else, returns 1
 */
int next(ll_iterator_t *iterator);

/**
 * @brief Safely frees all memory allocated to the iterator
 * 
 * @param iterator The iterator to destroy
 */
void destroy_iterator(ll_iterator_t *iterator);

/**
 * @brief Safely frees all memory allocated to a list
 * 
 * @param list The list to delete
 */
void destroy_list(linked_list_t *list);

#endif
