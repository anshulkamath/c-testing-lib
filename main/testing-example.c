#include "testing-logger.h"

void example_passing_test() {
    testing_logger_t *tester = create_tester();

    expect(tester, 1 == 1);
    expect(tester, 1);
    expect(tester, 40 + 2 == 42);

    log_tests(tester);
}

void example_failing_test() {
    testing_logger_t *tester = create_tester();

    expect(tester, 0 == 1);
    expect(tester, 0);
    expect(tester, 40 + 2 != 42);

    log_tests(tester);
}

int main() {
    example_passing_test();
    example_failing_test();

    return 0;
}
