#include <stdio.h>
#include <stdbool.h>

#include "input.h"
#include "test_helpers.h"

static const char *input_status_name(enum InputStatus status)
{
    switch (status)
    {
    case INPUT_STATUS_SUCCESS:
        return "INPUT_STATUS_SUCCESS";
    case INPUT_STATUS_INVALID_INPUT:
        return "INPUT_STATUS_INVALID_INPUT";
    case INPUT_STATUS_END_OF_FILE:
        return "INPUT_STATUS_END_OF_FILE";
    case INPUT_STATUS_IO_ERROR:
        return "INPUT_STATUS_IO_ERROR";
    case INPUT_STATUS_MEMORY_ERROR:
        return "INPUT_STATUS_MEMORY_ERROR";
    case INPUT_STATUS_INVALID_ARGUMENT:
        return "INPUT_STATUS_INVALID_ARGUMENT";
    default:
        return "UNKNOWN_INPUT_STATUS";
    }
}

static bool test_expect_input_status_equal(const char *test_id,
                                           enum InputStatus expected,
                                           enum InputStatus actual)
{
    if (actual == expected)
    {
        return true;
    }

    fprintf(stderr,
            "%s FAILED: expected input status = %s, actual = %s\n",
            test_id,
            input_status_name(expected),
            input_status_name(actual));
    return false;
}

static bool test_num_01(const char *test_id)
{
    const char *text = "12";
    double output = 0.0;

    enum InputStatus status = parse_number(text, &output);

    if (!test_expect_input_status_equal(test_id,
                                  INPUT_STATUS_SUCCESS,
                                  status))
    {
        return false;
    }

    return test_expect_double_near(test_id, 12.0, output, TEST_DOUBLE_TOLERANCE);
}

int main(void)
{
    const struct TestCase tests[] = {
        {"NUM-01", test_num_01},
    };

    return test_run_cases(tests, sizeof(tests) / sizeof(tests[0]));
}