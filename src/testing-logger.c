#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "testing-logger.h"
#include "tester-list.h"

typedef struct testing_logger {
    tester_list_t *failed_assertions;
    int failed;
} testing_logger_t;

const uint32_t MESSAGE_BYTES = 256;

testing_logger_t* create_tester() {
    testing_logger_t *tester = malloc(sizeof(testing_logger_t));

    tester->failed_assertions = t_create_list(MESSAGE_BYTES);
    tester->failed = 0;

    return tester;
}

void expect_helper(testing_logger_t *tester, int assertion, char* file, int line, char* expr) {
    // If the assertion passes, return
    if (assertion) return;

    char message[MESSAGE_BYTES];
    sprintf(message, "%s:%d -> expect(%s);", file, line, expr);
    
    t_push_back(tester->failed_assertions, message);
    tester->failed = 1;
}

void sprintf_tests_helper(testing_logger_t *tester, char *dest, const char* test_func) {
    if (!tester->failed) {
        sprintf(dest, "%s[PASS]%s %s\n", GRN, RESET, test_func);
        return;
    }

    tl_iterator_t *iter = t_create_iterator(tester->failed_assertions);

    char partial_message[MESSAGE_BYTES];
    char assertion[MESSAGE_BYTES];

    sprintf(partial_message, "%s[FAIL]%s %s\n", RED, RESET, test_func);
    strcat(dest, partial_message);

    // manages iterator memory
    do {
        t_peek(iter, assertion);
        sprintf(partial_message, "\t%s@%s %s%s%s\n", MAG, RESET, YEL, assertion, RESET);
        strcat(dest, partial_message);
    } while (t_next(iter));
}

void log_tests_helper(testing_logger_t *tester, const char* test_func) {
    size_t message_size = MESSAGE_BYTES * (1 + t_size(tester->failed_assertions));
    
    char dest[message_size];
    memset(dest, 0, message_size);

    sprintf_tests_helper(tester, dest, test_func); // memory neutral
    printf("%s", dest);

    destroy_tester(tester);
}

void destroy_tester(testing_logger_t *tester) {
    if (tester->failed_assertions) t_destroy_list(tester->failed_assertions);
    free(tester);
}
