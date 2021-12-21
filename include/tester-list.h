#ifndef TESTER_LIST_H
#define TESTER_LIST_H

#ifdef __cplusplus
extern 'C' {
#endif

#include <stdlib.h>

typedef struct tester_list tester_list_t;
typedef struct tl_iterator tl_iterator_t;

/**
 * @brief Create a list object
 * 
 * @param num_bytes The number of bytes allocated for each list entry
 * @return tester_list_t* The object that was created
 */
tester_list_t* t_create_list(size_t num_bytes);

/**
 * @brief Returns the size of a given list
 * 
 * @param list The list which we get the size of
 * @return size_t The size of the list
 */
size_t t_size(tester_list_t *list);

/**
 * @brief Get the head of the list
 * 
 * @param list The list to get the head of
 * @return char* A pointer to the head of the list
 */
char* t_get_head(tester_list_t *list);

/**
 * @brief Get the tail of the list
 * 
 * @param list The list to get the tail of
 * @return char* A pointer to the tail of the list
 */
char* t_get_tail(tester_list_t *list);

/**
 * @brief Append an element to the back of a list object
 * 
 * @param list The list object to which we append
 * @param val The value that is appended
 */
void t_push_back(tester_list_t *list, const char *insertee);

/**
 * @brief Create a iterator object
 * 
 * @param list The list over which to iterate
 * @return tl_iterator_t* A pointer to the iterator object that was created
 */
tl_iterator_t* t_create_iterator(tester_list_t *list);

/**
 * @brief Writes the value of which the iterator is currently pointing to dest
 * 
 * @param iterator The iterator to peek into
 * @param dest Where to put the data
 */
void t_peek(tl_iterator_t *iterator, char *dest);

/**
 * @brief Advances the iterator to the next element. If the iterator is at the
 *        end of the list, then the iterator will free itself and return 0.
 *        
 * @param iterator The iterator to advance
 * @return int Returns 0 if the iterator has been exhausted. Else, returns 1
 */
int t_next(tl_iterator_t *iterator);

/**
 * @brief Writes string representation of the given list to the given pointer
 * 
 * @param list The list to print the string representation of
 * @param dest The pointer to hold the string
 */
void t_sprint_list(tester_list_t *list, char *dest);

/**
 * @brief Safely frees all memory allocated to the iterator
 * 
 * @param iterator The iterator to destroy
 */
void t_destroy_iterator(tl_iterator_t *iterator);

/**
 * @brief Safely frees all memory allocated to a list
 * 
 * @param list The list to delete
 */
void t_destroy_list(tester_list_t *list);

#ifdef __cplusplus
}
#endif

#endif
