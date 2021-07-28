#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "testing-logger.h"

typedef struct testing_logger {
    char *failed_assertion;
    int failed;
} testing_logger_t;

const uint32_t MESSAGE_BYTES = 256;

testing_logger_t* create_tester() {
    testing_logger_t *tester = malloc(sizeof(testing_logger_t));

    tester->failed_assertion = NULL;
    tester->failed = 0;

    return tester;
}

void expect_helper(testing_logger_t *tester, int assertion, char* file, int line, char* expr) {
    // If an assertion has already failed, return
    if (tester->failed_assertion) return;

    // If the assertion passes, return
    if (assertion) return;

    char temp[256];
    sprintf(temp, "%s:%d -> expect(%s);", file, line, expr);
    
    tester->failed_assertion = malloc(MESSAGE_BYTES);
    memcpy(tester->failed_assertion, temp, MESSAGE_BYTES);
    tester->failed = 1;
}

void sprintf_tests_helper(testing_logger_t *tester, char *dest, const char* test_func) {
    if (!tester->failed)
        sprintf(dest, "%s[PASS]%s %s\n", GREEN, RESET, test_func);
    else
        sprintf(dest, "%s[FAIL]%s %s\n\t%s@%s %s%s%s\n", RED, RESET, test_func, MAG, RESET, YEL, tester->failed_assertion, RESET);
}

void log_tests_helper(testing_logger_t *tester, const char* test_func) {
    char dest[MESSAGE_BYTES];
    sprintf_tests_helper(tester, dest, test_func);
    printf("%s", dest);

    destroy_tester(tester);
}

void destroy_tester(testing_logger_t *tester) {
    free(tester->failed_assertion);
    free(tester);
}
