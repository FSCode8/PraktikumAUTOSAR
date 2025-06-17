#include "my_test.h"

// Test statistics are private to this file
static int tests_run = 0;
static int tests_passed = 0;
static int tests_failed = 0;

void test_suite_start(const char* suite_name) {
    printf("\n--- Testing %s ---\n", suite_name);
}

void test_summary() {
    printf("\n=== Test Summary ===\n");
    printf("Tests run: %d\n", tests_run);
    printf(GREEN "Passed: %d\n" RESET, tests_passed);
    if (tests_failed > 0) {
        printf(RED "Failed: %d\n" RESET, tests_failed);
    } else {
        printf("Failed: %d\n", tests_failed);
    }
    printf("Success rate: %.1f%%\n",
           tests_run > 0 ? (float)tests_passed / tests_run * 100.0f : 0.0f);
}

int get_test_result() {
    return tests_failed == 0 ? 0 : 1; // Return 0 if all tests passed
}

/* --- Internal Helper Function Definitions --- */

void _assert_true(int condition, const char* test_name, const char* file, int line) {
    tests_run++;
    if (condition) {
        printf(GREEN "PASS" RESET ": %s\n", test_name);
        tests_passed++;
    } else {
        printf(RED "FAIL" RESET ": %s - Condition was false at %s:%d\n", test_name, file, line);
        tests_failed++;
    }
}

void _assert_str_eq(const char* expected, const char* actual, const char* test_name, const char* file, int line) {
    tests_run++;
    if (actual != NULL && strcmp(expected, actual) == 0) {
        printf(GREEN "PASS" RESET ": %s\n", test_name);
        tests_passed++;
    } else {
        printf(RED "FAIL" RESET ": %s - Expected: \"%s\", Got: \"%s\" at %s:%d\n",
               test_name, expected, actual ? actual : "NULL", file, line);
        tests_failed++;
    }
}

void _assert_eq(long long expected, long long actual, const char* test_name, const char* file, int line) {
    tests_run++;
    if (expected == actual) {
        printf(GREEN "PASS" RESET ": %s\n", test_name);
        tests_passed++;
    } else {
        printf(RED "FAIL" RESET ": %s - Expected: %lld, Got: %lld at %s:%d\n",
               test_name, expected, actual, file, line);
        tests_failed++;
    }
}

void _assert_uint8_eq(uint8_t expected, uint8_t actual, const char* test_name, const char* file, int line) {
    tests_run++;
    if (expected == actual) {
        printf(GREEN "PASS" RESET ": %s\n", test_name);
        tests_passed++;
    } else {
        printf(RED "FAIL" RESET ": %s - Expected: 0x%02X, Got: 0x%02X at %s:%d\n",
               test_name, expected, actual, file, line);
        tests_failed++;
    }
}