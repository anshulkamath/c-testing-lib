#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "testing.h"

typedef struct testing_logger {
    char *failed_assertion;
    int failed;
} testing_logger_t;

testing_logger_t* init_tester() {
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
    
    tester->failed_assertion = malloc(256);
    memcpy(tester->failed_assertion, temp, 256);
    tester->failed = 1;
}

void log_tests_helper(testing_logger_t *tester, const char* test_func) {
    if (!tester->failed)
        printf("%s[PASS]%s %s\n", GREEN, RESET, test_func);
    else
        printf("%s[FAIL]%s %s\n\t%s@%s %s%s%s\n", RED, RESET, test_func, MAG, RESET, YEL, tester->failed_assertion, RESET);

    // tester is no longer used, so free its memory
    free(tester->failed_assertion);
    free(tester);
}
