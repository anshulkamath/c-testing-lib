#include "linked-list.h"
#include "testing-logger.h"
#include <string.h>
#include <stdio.h>

const size_t NUM_BYTES = 256;

// Helper function
int compare_string(const char *a, const char *b) {
    return strcmp(a, b) == 0;
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
    expect(tester, !strcmp(get_head(list), "up!"));
    expect(tester, !strcmp(get_tail(list), "up!"));

    push_front(list, "give you ");
    expect(tester, size(list) == 2);
    expect(tester, !strcmp(get_head(list), "give you "));
    expect(tester, !strcmp(get_tail(list), "up!"));

    push_front(list, "Never gonna ");
    expect(tester, size(list) == 3);
    expect(tester, !strcmp(get_head(list), "Never gonna "));
    expect(tester, !strcmp(get_tail(list), "up!"));

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
    expect(tester, !strcmp(get_head(list), "Never gonna "));
    expect(tester, !strcmp(get_tail(list), "Never gonna "));

    push_back(list, "let you ");
    expect(tester, size(list) == 2);
    expect(tester, !strcmp(get_head(list), "Never gonna "));
    expect(tester, !strcmp(get_tail(list), "let you "));

    push_back(list, "down");
    expect(tester, size(list) == 3);
    expect(tester, !strcmp(get_head(list), "Never gonna "));
    expect(tester, !strcmp(get_tail(list), "down"));

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
    expect(tester, !strcmp(res, "Never gonna "));
    expect(tester, !strcmp(get_head(list), "run around and "));
    expect(tester, !strcmp(get_tail(list), "desert you!"));

    pop_front(list, res);
    expect(tester, !strcmp(res, "run around and "));
    expect(tester, !strcmp(get_head(list), "desert you!"));
    expect(tester, !strcmp(get_tail(list), "desert you!"));

    pop_front(list, res);
    expect(tester, !strcmp(res, "desert you!"));
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
    expect(tester, !strcmp(res, "desert you!"));
    expect(tester, !strcmp(get_head(list), "Never gonna "));
    expect(tester, !strcmp(get_tail(list), "run around and "));

    pop_back(list, res);
    expect(tester, !strcmp(res, "run around and "));
    expect(tester, !strcmp(get_head(list), "Never gonna "));
    expect(tester, !strcmp(get_tail(list), "Never gonna "));

    pop_back(list, res);
    expect(tester, !strcmp(res, "Never gonna "));
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
    expect(tester, !strcmp(res, ""));
    
    get(list, 3, res);
    expect(tester, !strcmp(res, ""));

    // valid gets
    get(list, 0, res);
    expect(tester, !strcmp(res, "Never gonna "));

    get(list, 1, res);
    expect(tester, !strcmp(res, "run around and "));

    get(list, 2, res);
    expect(tester, !strcmp(res, "desert you!"));

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

    return 0;
}
