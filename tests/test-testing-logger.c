#include "testing-logger.h"
#include <stdio.h>
#include <string.h>

void test_working_tests() {
    testing_logger_t *tester1 = create_tester();
    testing_logger_t *tester2 = create_tester();
    char dest[MESSAGE_BYTES];
    char expected[MESSAGE_BYTES];

    memset(dest, 0, MESSAGE_BYTES);
    memset(expected, 0, MESSAGE_BYTES);

    const char function[] = "test_working_tests";

    expect(tester1, 5 == 5); // should be fine
    expect(tester1, 1); // should be fine

    sprintf(expected, "%s[PASS]%s %s\n", GRN, RESET, function);
    sprintf_tests(tester1, dest);

    expect(tester2, !strcmp(dest, expected));

    destroy_tester(tester1);
    log_tests(tester2);
}

void test_semi_working_tests() {
    testing_logger_t *tester1 = create_tester();
    testing_logger_t *tester2 = create_tester();
    char dest[MESSAGE_BYTES];
    char expected[MESSAGE_BYTES];

    memset(dest, 0, MESSAGE_BYTES);
    memset(expected, 0, MESSAGE_BYTES);

    const char file[] = "tests/test-testing-logger.c";
    const char function[] = "test_semi_working_tests";
    const int line_no = 42;

    expect(tester1, 5 == 5); // should be fine
    expect(tester1, 0); // should not be fine

    sprintf(expected,
        "%s[FAIL]%s %s\n"
        "\t%s@%s %s%s:%d -> expect(0);%s\n",
        RED, RESET, function,
        MAG, RESET, YEL, file, line_no, RESET
    );
    sprintf_tests(tester1, dest);

    expect(tester2, !strcmp(dest, expected));

    destroy_tester(tester1);
    log_tests(tester2);
}

void test_semi_working_tests_2() {
    testing_logger_t *tester1 = create_tester();
    testing_logger_t *tester2 = create_tester();
    char dest[MESSAGE_BYTES];
    char expected[MESSAGE_BYTES];

    memset(dest, 0, MESSAGE_BYTES);
    memset(expected, 0, MESSAGE_BYTES);

    const char file[] = "tests/test-testing-logger.c";
    const char function[] = "test_semi_working_tests_2";
    const int line_no = 71;

    expect(tester1, 5 == 0); // should not be fine
    expect(tester1, 1); // should be fine

    sprintf(expected,
        "%s[FAIL]%s %s\n"
        "\t%s@%s %s%s:%d -> expect(5 == 0);%s\n",
        RED, RESET, function,
        MAG, RESET, YEL, file, line_no, RESET
    );
    sprintf_tests(tester1, dest);

    expect(tester2, !strcmp(dest, expected));
    
    destroy_tester(tester1);
    log_tests(tester2);
}

void test_non_working_tests() {
    testing_logger_t *tester1 = create_tester();
    testing_logger_t *tester2 = create_tester();
    char dest[MESSAGE_BYTES];
    char expected[MESSAGE_BYTES];

    memset(dest, 0, MESSAGE_BYTES);
    memset(expected, 0, MESSAGE_BYTES);

    const char file[] = "tests/test-testing-logger.c";
    const char function[] = "test_non_working_tests";
    const int line_no1 = 102;
    const int line_no2 = 103;

    expect(tester1, 7 == 0); // should not be fine
    expect(tester1, 0); // should not be fine

    sprintf(expected,
        "%s[FAIL]%s %s\n"
        "\t%s@%s %s%s:%d -> expect(7 == 0);%s\n"
        "\t%s@%s %s%s:%d -> expect(0);%s\n",
        RED, RESET, function,
        MAG, RESET, YEL, file, line_no1, RESET,
        MAG, RESET, YEL, file, line_no2, RESET
    );
    sprintf_tests(tester1, dest);

    expect(tester2, !strcmp(dest, expected));

    destroy_tester(tester1);
    log_tests(tester2);
}

void test_many_broken_tests() {
    testing_logger_t *tester1 = create_tester();
    testing_logger_t *tester2 = create_tester();
    char dest[MESSAGE_BYTES * 3];
    char expected[MESSAGE_BYTES * 3];

    memset(dest, 0, MESSAGE_BYTES * 3);
    memset(expected, 0, MESSAGE_BYTES * 3);

    const char file[] = "tests/test-testing-logger.c";
    const char function[] = "test_many_broken_tests";
    const int line_no1 = 137;
    const int line_no2 = 138;
    const int line_no3 = 139;
    const int line_no4 = 142;

    expect(tester1, 7 == 0); // should not be fine
    expect(tester1, 6 == 0); // should not be fine
    expect(tester1, 5 == 0); // should not be fine
    expect(tester1, 1);      // should be fine
    expect(tester1, 1 == 1); // should be fine
    expect(tester1, 0 == 5); // should not be fine

    sprintf(expected,
        "%s[FAIL]%s %s\n"
        "\t%s@%s %s%s:%d -> expect(7 == 0);%s\n"
        "\t%s@%s %s%s:%d -> expect(6 == 0);%s\n"
        "\t%s@%s %s%s:%d -> expect(5 == 0);%s\n"
        "\t%s@%s %s%s:%d -> expect(0 == 5);%s\n",
        RED, RESET, function,
        MAG, RESET, YEL, file, line_no1, RESET,
        MAG, RESET, YEL, file, line_no2, RESET,
        MAG, RESET, YEL, file, line_no3, RESET,
        MAG, RESET, YEL, file, line_no4, RESET
    );
    sprintf_tests(tester1, dest);

    expect(tester2, !strcmp(dest, expected));

    destroy_tester(tester1);
    log_tests(tester2);
}

int main() {
    test_working_tests();
    test_semi_working_tests();
    test_semi_working_tests_2();
    test_non_working_tests();
    test_many_broken_tests();

    return 0;
}
