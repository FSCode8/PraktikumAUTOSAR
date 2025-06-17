#ifndef MY_TEST_H
#define MY_TEST_H

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>

// Color codes for output (optional)
#define GREEN "\033[0;32m"
#define RED   "\033[0;31m"
#define RESET "\033[0m"

/* --- Public Function Declarations --- */

// Call this at the beginning of a test suite for clarity
void test_suite_start(const char* suite_name);

// Call this to print the final summary
void test_summary();

// Call this to get an exit code for your main() function
int get_test_result();


/* --- Assertion Macros --- */
// These macros need to be in the header file so they can be used by any test file.
// We make them call internal functions to avoid cluttering the header.

#define ASSERT_TRUE(condition, test_name) \
    _assert_true((condition), (test_name), __FILE__, __LINE__)

#define ASSERT_STR_EQ(expected, actual, test_name) \
    _assert_str_eq((expected), (actual), (test_name), __FILE__, __LINE__)

#define ASSERT_EQ(expected, actual, test_name) \
    _assert_eq((long long)(expected), (long long)(actual), (test_name), __FILE__, __LINE__)

/* --- Internal Helper Function Declarations (for use by macros) --- */
// These are not meant to be called directly by the user, but the macros need them.
void _assert_true(int condition, const char* test_name, const char* file, int line);
void _assert_str_eq(const char* expected, const char* actual, const char* test_name, const char* file, int line);
void _assert_eq(long long expected, long long actual, const char* test_name, const char* file, int line);

#endif // MY_TEST_H