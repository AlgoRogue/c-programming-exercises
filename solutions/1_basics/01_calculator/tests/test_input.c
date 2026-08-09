#include <float.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

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

static const char *calc_op_name(enum CalcOp op)
{
    switch (op)
    {
    case CALC_OP_ADD:
        return "CALC_OP_ADD";
    case CALC_OP_SUBTRACT:
        return "CALC_OP_SUBTRACT";
    case CALC_OP_MULTIPLY:
        return "CALC_OP_MULTIPLY";
    case CALC_OP_DIVIDE:
        return "CALC_OP_DIVIDE";
    default:
        return "UNKNOWN_CALC_OP";
    }
}

static bool test_expect_calc_op_equal(const char *test_id,
                                      enum CalcOp expected,
                                      enum CalcOp actual)
{
    if (actual == expected)
    {
        return true;
    }

    fprintf(stderr,
            "%s FAILED: expected calculation operation = %s, actual = %s\n",
            test_id,
            calc_op_name(expected),
            calc_op_name(actual));
    return false;
}

static bool test_expect_valid_operation(const char *test_id,
                                        const char *text,
                                        enum CalcOp expected)
{
    enum CalcOp output = CALC_OP_DIVIDE;
    enum InputStatus status = parse_operation(text, &output);

    if (!test_expect_input_status_equal(test_id, INPUT_STATUS_SUCCESS, status))
    {
        return false;
    }

    return test_expect_calc_op_equal(test_id, expected, output);
}

static bool test_expect_invalid_operation(const char *test_id, const char *text)
{
    enum CalcOp output = CALC_OP_DIVIDE;
    enum InputStatus status = parse_operation(text, &output);

    if (!test_expect_input_status_equal(test_id,
                                        INPUT_STATUS_INVALID_INPUT,
                                        status))
    {
        return false;
    }

    return test_expect_calc_op_equal(test_id, CALC_OP_DIVIDE, output);
}


static bool test_expect_valid_number(const char *test_id,
                                     const char *text,
                                     double expected)
{
    double output = 0.0;
    enum InputStatus status = parse_number(text, &output);

    if (!test_expect_input_status_equal(test_id, INPUT_STATUS_SUCCESS, status))
    {
        return false;
    }

    return test_expect_double_near(test_id,
                                   expected,
                                   output,
                                   TEST_DOUBLE_TOLERANCE);
}

static bool test_expect_invalid_number(const char *test_id, const char *text)
{
    const double sentinel = 1234.5;
    double output = sentinel;
    enum InputStatus status = parse_number(text, &output);

    if (!test_expect_input_status_equal(test_id,
                                        INPUT_STATUS_INVALID_INPUT,
                                        status))
    {
        return false;
    }

    return test_expect_double_near(test_id,
                                   sentinel,
                                   output,
                                   TEST_DOUBLE_TOLERANCE);
}

static bool test_num_01(const char *test_id)
{
    return test_expect_valid_number(test_id, "12", 12.0);
}

static bool test_num_02(const char *test_id)
{
    return test_expect_valid_number(test_id, "-12", -12.0);
}

static bool test_num_03(const char *test_id)
{
    return test_expect_valid_number(test_id, "+12.5", 12.5);
}

static bool test_num_04(const char *test_id)
{
    return test_expect_valid_number(test_id, "12.5", 12.5);
}

static bool test_num_05(const char *test_id)
{
    return test_expect_valid_number(test_id, ".5", 0.5);
}

static bool test_num_06(const char *test_id)
{
    return test_expect_valid_number(test_id, "5.", 5.0);
}

static bool test_num_07(const char *test_id)
{
    return test_expect_valid_number(test_id, "  -2.5  ", -2.5);
}

static bool test_num_08(const char *test_id)
{
    return test_expect_valid_number(test_id, "0", 0.0) &&
           test_expect_valid_number(test_id, "-0", -0.0) &&
           test_expect_valid_number(test_id, "0.0", 0.0);
}

static bool test_num_09(const char *test_id)
{
    return test_expect_invalid_number(test_id, "") &&
           test_expect_invalid_number(test_id, "   ");
}

static bool test_num_10(const char *test_id)
{
    return test_expect_invalid_number(test_id, "+") &&
           test_expect_invalid_number(test_id, "-") &&
           test_expect_invalid_number(test_id, ".");
}

static bool test_num_11(const char *test_id)
{
    return test_expect_invalid_number(test_id, "1.2.3");
}

static bool test_num_12(const char *test_id)
{
    return test_expect_invalid_number(test_id, "1 2") &&
           test_expect_invalid_number(test_id, "- 2");
}

static bool test_num_13(const char *test_id)
{
    return test_expect_invalid_number(test_id, "12,5");
}

static bool test_num_14(const char *test_id)
{
    return test_expect_invalid_number(test_id, "1.5e3");
}

static bool test_num_15(const char *test_id)
{
    return test_expect_invalid_number(test_id, "inf") &&
           test_expect_invalid_number(test_id, "nan");
}

static bool test_num_16(const char *test_id)
{
    return test_expect_invalid_number(test_id, "12abc");
}

static bool test_num_17(const char *test_id)
{
    char text[DBL_MAX_10_EXP + 2];

    memset(text, '9', sizeof(text) - 1);
    text[sizeof(text) - 1] = '\0';

    return test_expect_invalid_number(test_id, text);
}

static bool test_op_01(const char *test_id)
{
    return test_expect_valid_operation(test_id, "+", CALC_OP_ADD);
}

static bool test_op_02(const char *test_id)
{
    return test_expect_valid_operation(test_id, "-", CALC_OP_SUBTRACT);
}

static bool test_op_03(const char *test_id)
{
    return test_expect_valid_operation(test_id, "*", CALC_OP_MULTIPLY);
}

static bool test_op_04(const char *test_id)
{
    return test_expect_valid_operation(test_id, "x", CALC_OP_MULTIPLY);
}

static bool test_op_05(const char *test_id)
{
    return test_expect_valid_operation(test_id, "/", CALC_OP_DIVIDE);
}

static bool test_op_06(const char *test_id)
{
    return test_expect_valid_operation(test_id, "\t x \n", CALC_OP_MULTIPLY);
}

static bool test_op_07(const char *test_id)
{
    return test_expect_invalid_operation(test_id, "") &&
           test_expect_invalid_operation(test_id, "   ");
}

static bool test_op_08(const char *test_id)
{
    return test_expect_invalid_operation(test_id, "%");
}

static bool test_op_09(const char *test_id)
{
    return test_expect_invalid_operation(test_id, "++") &&
           test_expect_invalid_operation(test_id, "+-");
}

int main(void)
{
    const struct TestCase tests[] = {
        {"NUM-01", test_num_01},
        {"NUM-02", test_num_02},
        {"NUM-03", test_num_03},
        {"NUM-04", test_num_04},
        {"NUM-05", test_num_05},
        {"NUM-06", test_num_06},
        {"NUM-07", test_num_07},
        {"NUM-08", test_num_08},
        {"NUM-09", test_num_09},
        {"NUM-10", test_num_10},
        {"NUM-11", test_num_11},
        {"NUM-12", test_num_12},
        {"NUM-13", test_num_13},
        {"NUM-14", test_num_14},
        {"NUM-15", test_num_15},
        {"NUM-16", test_num_16},
        {"NUM-17", test_num_17},
        {"OP-01", test_op_01},
        {"OP-02", test_op_02},
        {"OP-03", test_op_03},
        {"OP-04", test_op_04},
        {"OP-05", test_op_05},
        {"OP-06", test_op_06},
        {"OP-07", test_op_07},
        {"OP-08", test_op_08},
        {"OP-09", test_op_09},
    };

    return test_run_cases(tests, sizeof(tests) / sizeof(tests[0]));
}