#include "testing.h"

void test_working_tests() {
    testing_logger_t *tester = init_tester();

    expect(tester, 5 == 5); // should be fine
    expect(tester, 1); // should be fine

    log_tests(tester);
}

void test_semi_working_tests() {
    testing_logger_t *tester = init_tester();

    expect(tester, 5 == 5); // should be fine
    expect(tester, 0); // should not be fine

    log_tests(tester);
}

void test_semi_working_tests_2() {
    testing_logger_t *tester = init_tester();

    expect(tester, 5 == 0); // should not be fine
    expect(tester, 1); // should be fine
    
    log_tests(tester);
}

void test_non_working_tests() {
    testing_logger_t *tester = init_tester();

    expect(tester, 5 == 0); // should not be fine
    expect(tester, 0); // should not be fine

    log_tests(tester);
}

int main() {
    test_working_tests();
    test_semi_working_tests();
    test_semi_working_tests_2();
    test_non_working_tests();

    return 0;
}
