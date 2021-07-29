#include "tester-list.h"
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
    tester_list_t *list = t_create_list(NUM_BYTES);

    expect(tester, t_size(list) == 0);

    // destroy testing variables
    t_destroy_list(list);
    log_tests(tester);
}

void test_push_back() {
    // initialize testing variables
    testing_logger_t *tester = create_tester();
    tester_list_t *list = t_create_list(NUM_BYTES);

    expect(tester, t_size(list) == 0);

    t_push_back(list, "Never gonna ");
    expect(tester, t_size(list) == 1);
    expect(tester, compare_string(t_get_head(list), "Never gonna "));
    expect(tester, compare_string(t_get_tail(list), "Never gonna "));

    t_push_back(list, "let you ");
    expect(tester, t_size(list) == 2);
    expect(tester, compare_string(t_get_head(list), "Never gonna "));
    expect(tester, compare_string(t_get_tail(list), "let you "));

    t_push_back(list, "down");
    expect(tester, t_size(list) == 3);
    expect(tester, compare_string(t_get_head(list), "Never gonna "));
    expect(tester, compare_string(t_get_tail(list), "down"));

    // destroy testing variables
    t_destroy_list(list);
    log_tests(tester);
}

void test_iterator() {
    // initialize testing variables
    testing_logger_t *tester = create_tester();
    tester_list_t *list = t_create_list(NUM_BYTES);
    char res[NUM_BYTES];
    
    // GIVEN:
    t_push_back(list, "Never gonna ");
    t_push_back(list, "run around and ");
    t_push_back(list, "desert you!");

    tl_iterator_t *iter = t_create_iterator(list);

    t_peek(iter, res);
    expect(tester, compare_string(res, "Never gonna "));
    expect(tester, t_next(iter));

    t_peek(iter, res);
    expect(tester, compare_string(res, "run around and "));
    expect(tester, t_next(iter));

    t_peek(iter, res);
    expect(tester, compare_string(res, "desert you!"));
    expect(tester, !t_next(iter));

    // destroy testing variables
    t_destroy_list(list);
    log_tests(tester);
}

void test_sprint_list() {
    // initialize testing variables
    testing_logger_t *tester = create_tester();
    tester_list_t *list = t_create_list(NUM_BYTES);
    char res[3 * NUM_BYTES];
    
    // GIVEN:
    t_push_back(list, "Never gonna");
    t_push_back(list, "run around and");
    t_push_back(list, "desert you!");

    t_sprint_list(list, res);
    expect(tester, compare_string(res, "Never gonna run around and desert you!"));

    // destroy testing variables
    t_destroy_list(list);
    log_tests(tester);
}

int main() {
    test_empty_list_attr();
    test_push_back();
    test_iterator();
    test_sprint_list();

    return 0;
}
