#include "testing-logger.h"
#include <stdio.h>
#include <string.h>

void test_working_tests() {
    testing_logger_t *tester1 = init_tester();
    testing_logger_t *tester2 = init_tester();
    char dest[MESSAGE_BYTES];
    char expected[MESSAGE_BYTES];

    const char function[] = "test_working_tests";

    expect(tester1, 5 == 5); // should be fine
    expect(tester1, 1); // should be fine

    sprintf(expected, "\x1b[32m[PASS]\x1b[0m %s\n", function);
    sprintf_tests(tester1, dest);

    expect(tester2, !strcmp(dest, expected));

    free_logger(tester1);
    log_tests(tester2);
}

void test_semi_working_tests() {
    testing_logger_t *tester1 = init_tester();
    testing_logger_t *tester2 = init_tester();
    char dest[MESSAGE_BYTES];
    char expected[MESSAGE_BYTES];

    const char file[] = "tests/test-testing-logger.c";
    const char function[] = "test_semi_working_tests";
    const int line_no = 36;

    expect(tester1, 5 == 5); // should be fine
    expect(tester1, 0); // should not be fine

    sprintf(expected, "\x1b[31m[FAIL]\x1b[0m %s\n\t\x1b[35m@\x1b[0m \x1b[0m%s:%d -> expect(0);\x1b[0m\n", function, file, line_no);
    sprintf_tests(tester1, dest);

    expect(tester2, !strcmp(dest, expected));

    free_logger(tester1);
    log_tests(tester2);
}

void test_semi_working_tests_2() {
    testing_logger_t *tester1 = init_tester();
    testing_logger_t *tester2 = init_tester();
    char dest[MESSAGE_BYTES];
    char expected[MESSAGE_BYTES];

    const char file[] = "tests/test-testing-logger.c";
    const char function[] = "test_semi_working_tests_2";
    const int line_no = 57;

    expect(tester1, 5 == 0); // should not be fine
    expect(tester1, 1); // should be fine

    sprintf(expected, "\x1b[31m[FAIL]\x1b[0m %s\n\t\x1b[35m@\x1b[0m \x1b[0m%s:%d -> expect(5 == 0);\x1b[0m\n", function, file, line_no);
    sprintf_tests(tester1, dest);

    expect(tester2, !strcmp(dest, expected));
    
    free_logger(tester1);
    log_tests(tester2);
}

void test_non_working_tests() {
    testing_logger_t *tester1 = init_tester();
    testing_logger_t *tester2 = init_tester();
    char dest[MESSAGE_BYTES];
    char expected[MESSAGE_BYTES];

    const char file[] = "tests/test-testing-logger.c";
    const char function[] = "test_non_working_tests";
    const int line_no = 79;

    expect(tester1, 7 == 0); // should not be fine
    expect(tester1, 0); // should not be fine

    sprintf(expected, "\x1b[31m[FAIL]\x1b[0m %s\n\t\x1b[35m@\x1b[0m \x1b[0m%s:%d -> expect(7 == 0);\x1b[0m\n", function, file, line_no);
    sprintf_tests(tester1, dest);

    expect(tester2, !strcmp(dest, expected));

    free_logger(tester1);
    log_tests(tester2);
}

int main() {
    test_working_tests();
    test_semi_working_tests();
    test_semi_working_tests_2();
    test_non_working_tests();

    return 0;
}
