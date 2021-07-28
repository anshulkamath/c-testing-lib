#include "linked-list.h"
#include "testing-logger.h"
#include <string.h>
#include <stdio.h>

const size_t NUM_BYTES = 256;

// Helper function
int compare_string(const void *a, const void *b) {
    return strcmp((char *)a, (char *)b) == 0;
}

void test_empty_list_attr() {
    // initialize testing variables
    testing_logger_t *tester = create_tester();
    linked_list_t *list = create_list(NUM_BYTES);

    expect(tester, size(list) == 0);
    expect(tester, get_num_bytes(list) == NUM_BYTES);
    expect(tester, get_head(list) == NULL);
    expect(tester, get_tail(list) == NULL);

    // destroy testing variables
    destroy_list(list);
    log_tests(tester);
}

void test_push_front() {
    // initialize testing variables
    testing_logger_t *tester = create_tester();
    linked_list_t *list = create_list(NUM_BYTES);

    expect(tester, size(list) == 0);

    push_front(list, "up!");
    expect(tester, size(list) == 1);
    expect(tester, compare_string(get_head(list), "up!"));
    expect(tester, compare_string(get_tail(list), "up!"));

    push_front(list, "give you ");
    expect(tester, size(list) == 2);
    expect(tester, compare_string(get_head(list), "give you "));
    expect(tester, compare_string(get_tail(list), "up!"));

    push_front(list, "Never gonna ");
    expect(tester, size(list) == 3);
    expect(tester, compare_string(get_head(list), "Never gonna "));
    expect(tester, compare_string(get_tail(list), "up!"));

    // destroy testing variables
    destroy_list(list);
    log_tests(tester);
}

void test_push_back() {
    // initialize testing variables
    testing_logger_t *tester = create_tester();
    linked_list_t *list = create_list(NUM_BYTES);

    expect(tester, size(list) == 0);

    push_back(list, "Never gonna ");
    expect(tester, size(list) == 1);
    expect(tester, compare_string(get_head(list), "Never gonna "));
    expect(tester, compare_string(get_tail(list), "Never gonna "));

    push_back(list, "let you ");
    expect(tester, size(list) == 2);
    expect(tester, compare_string(get_head(list), "Never gonna "));
    expect(tester, compare_string(get_tail(list), "let you "));

    push_back(list, "down");
    expect(tester, size(list) == 3);
    expect(tester, compare_string(get_head(list), "Never gonna "));
    expect(tester, compare_string(get_tail(list), "down"));

    // destroy testing variables
    destroy_list(list);
    log_tests(tester);
}

void test_pop_front() {
    // initialize testing variables
    testing_logger_t *tester = create_tester();
    linked_list_t *list = create_list(NUM_BYTES);
    char res[NUM_BYTES];
    
    // GIVEN:
    push_back(list, "Never gonna ");
    push_back(list, "run around and ");
    push_back(list, "desert you!");

    // WHEN:
    pop_front(list, res);
    expect(tester, compare_string(res, "Never gonna "));
    expect(tester, compare_string(get_head(list), "run around and "));
    expect(tester, compare_string(get_tail(list), "desert you!"));

    pop_front(list, res);
    expect(tester, compare_string(res, "run around and "));
    expect(tester, compare_string(get_head(list), "desert you!"));
    expect(tester, compare_string(get_tail(list), "desert you!"));

    pop_front(list, res);
    expect(tester, compare_string(res, "desert you!"));
    expect(tester, get_head(list) == NULL);
    expect(tester, get_tail(list) == NULL);

    expect(tester, size(list) == 0);

    // destroy testing variables
    destroy_list(list);
    log_tests(tester);
}

void test_pop_back() {
    // initialize testing variables
    testing_logger_t *tester = create_tester();
    linked_list_t *list = create_list(NUM_BYTES);
    char res[NUM_BYTES];
    
    // GIVEN:
    push_back(list, "Never gonna ");
    push_back(list, "run around and ");
    push_back(list, "desert you!");

    // WHEN:
    pop_back(list, res);
    expect(tester, compare_string(res, "desert you!"));
    expect(tester, compare_string(get_head(list), "Never gonna "));
    expect(tester, compare_string(get_tail(list), "run around and "));

    pop_back(list, res);
    expect(tester, compare_string(res, "run around and "));
    expect(tester, compare_string(get_head(list), "Never gonna "));
    expect(tester, compare_string(get_tail(list), "Never gonna "));

    pop_back(list, res);
    expect(tester, compare_string(res, "Never gonna "));
    expect(tester, get_head(list) == NULL);
    expect(tester, get_tail(list) == NULL);

    expect(tester, size(list) == 0);

    // destroy testing variables
    destroy_list(list);
    log_tests(tester);
}

void test_contains() {
    // initialize testing variables
    testing_logger_t *tester = create_tester();
    linked_list_t *list = create_list(NUM_BYTES);
    set_comparator(list, compare_string);
    
    // GIVEN:
    push_back(list, "Never gonna ");
    push_back(list, "run around and ");
    push_back(list, "desert you!");

    expect(tester, contains(list, "Never gonna "));
    expect(tester, !contains(list, "let you down"));

    // destroy testing variables
    destroy_list(list);
    log_tests(tester);
}

void test_get() {
    // initialize testing variables
    testing_logger_t *tester = create_tester();
    linked_list_t *list = create_list(NUM_BYTES);
    char res[256] = ""; // manually set size to allow for initialized value
    
    // GIVEN:
    push_back(list, "Never gonna ");
    push_back(list, "run around and ");
    push_back(list, "desert you!");

    // invalid gets
    get(list, -1, res);
    expect(tester, compare_string(res, ""));
    
    get(list, 3, res);
    expect(tester, compare_string(res, ""));

    // valid gets
    get(list, 0, res);
    expect(tester, compare_string(res, "Never gonna "));

    get(list, 1, res);
    expect(tester, compare_string(res, "run around and "));

    get(list, 2, res);
    expect(tester, compare_string(res, "desert you!"));

    // destroy testing variables
    destroy_list(list);
    log_tests(tester);
}

void test_list_insert() {
    // initialize testing variables
    testing_logger_t *tester = create_tester();
    linked_list_t *list = create_list(NUM_BYTES);
    char res[NUM_BYTES];
    
    // GIVEN:
    push_back(list, "Never gonna ");
    push_back(list, "run around and ");
    push_back(list, "desert you!");

    // invalid inserts
    list_insert(list, -1, "");
    expect(tester, size(list) == 3);
    expect(tester, compare_string(get_head(list), "Never gonna "));
    expect(tester, compare_string(get_tail(list), "desert you!"));
    
    list_insert(list, 4, "");
    expect(tester, size(list) == 3);
    expect(tester, compare_string(get_head(list), "Never gonna "));
    expect(tester, compare_string(get_tail(list), "desert you!"));

    // valid inserts
    list_insert(list, 0, "ba");
    get(list, 0, res);
    expect(tester, size(list) == 4);
    expect(tester, compare_string(res, "ba"));
    expect(tester, compare_string(get_head(list), "ba"));
    expect(tester, compare_string(get_tail(list), "desert you!"));

    list_insert(list, 2, "dum");
    get(list, 2, res);
    expect(tester, size(list) == 5);
    expect(tester, compare_string(res, "dum"));
    expect(tester, compare_string(get_head(list), "ba"));
    expect(tester, compare_string(get_tail(list), "desert you!"));

    list_insert(list, 5, "taa");
    get(list, 5, res);
    expect(tester, size(list) == 6);
    expect(tester, compare_string(res, "taa"));
    expect(tester, compare_string(get_head(list), "ba"));
    expect(tester, compare_string(get_tail(list), "taa"));

    // destroy testing variables
    destroy_list(list);
    log_tests(tester);
}

void test_list_delete() {
    // initialize testing variables
    testing_logger_t *tester = create_tester();
    linked_list_t *list = create_list(NUM_BYTES);
    char res[NUM_BYTES];
    
    // GIVEN:
    push_back(list, "ba");
    push_back(list, "Never gonna ");
    push_back(list, "dum");
    push_back(list, "run around and ");
    push_back(list, "desert you!");
    push_back(list, "taa");

    // invalid deletes
    list_delete(list, -1, res);
    expect(tester, size(list) == 6);
    expect(tester, compare_string(get_head(list), "ba"));
    expect(tester, compare_string(get_tail(list), "taa"));
    
    list_delete(list, 7, res);
    expect(tester, size(list) == 6);
    expect(tester, compare_string(get_head(list), "ba"));
    expect(tester, compare_string(get_tail(list), "taa"));

    // valid deletes
    list_delete(list, 0, res);
    expect(tester, size(list) == 5);
    expect(tester, compare_string(res, "ba"));
    expect(tester, compare_string(get_head(list), "Never gonna "));
    expect(tester, compare_string(get_tail(list), "taa"));

    list_delete(list, 1, res);
    expect(tester, size(list) == 4);
    expect(tester, compare_string(res, "dum"));
    expect(tester, compare_string(get_head(list), "Never gonna "));
    expect(tester, compare_string(get_tail(list), "taa"));

    list_delete(list, 3, res);
    expect(tester, size(list) == 3);
    expect(tester, compare_string(res, "taa"));
    expect(tester, compare_string(get_head(list), "Never gonna "));
    expect(tester, compare_string(get_tail(list), "desert you!"));

    // destroy testing variables
    destroy_list(list);
    log_tests(tester);
}

void test_iterator() {
    // initialize testing variables
    testing_logger_t *tester = create_tester();
    linked_list_t *list = create_list(NUM_BYTES);
    char res[NUM_BYTES];
    
    // GIVEN:
    push_back(list, "Never gonna ");
    push_back(list, "run around and ");
    push_back(list, "desert you!");

    ll_iterator_t *iter = create_iterator(list);

    peek(iter, res);
    expect(tester, compare_string(res, "Never gonna "));
    expect(tester, has_next(iter));
    expect(tester, next(iter));

    peek(iter, res);
    expect(tester, compare_string(res, "run around and "));
    expect(tester, has_next(iter));
    expect(tester, next(iter));

    peek(iter, res);
    expect(tester, compare_string(res, "desert you!"));
    expect(tester, !has_next(iter));
    expect(tester, !next(iter));

    // destroy testing variables
    destroy_list(list);
    log_tests(tester);
}

void test_sprint_list() {
    // initialize testing variables
    testing_logger_t *tester = create_tester();
    linked_list_t *list = create_list(NUM_BYTES);
    char res[3 * NUM_BYTES];
    
    // GIVEN:
    push_back(list, "Never gonna");
    push_back(list, "run around and");
    push_back(list, "desert you!");

    sprint_list(list, res);
    expect(tester, compare_string(res, "Never gonna run around and desert you!"));

    // destroy testing variables
    destroy_list(list);
    log_tests(tester);
}

int main() {
    test_empty_list_attr();
    test_push_front();
    test_push_back();
    test_pop_front();
    test_pop_back();
    test_contains();
    test_get();
    test_list_insert();
    test_list_delete();
    test_iterator();
    test_sprint_list();

    return 0;
}
