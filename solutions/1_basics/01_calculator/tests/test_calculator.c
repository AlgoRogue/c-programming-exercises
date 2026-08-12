#include <stdio.h>
#include <stdbool.h>

#include "calculator.h"
#include "test_helpers.h"

static const char *calc_status_name(enum CalcStatus status)
{
    switch (status)
    {
    case CALC_STATUS_SUCCESS:
        return "CALC_STATUS_SUCCESS";
    case CALC_STATUS_UNSUPPORTED_OPERATION:
        return "CALC_STATUS_UNSUPPORTED_OPERATION";
    case CALC_STATUS_DIVISION_BY_ZERO:
        return "CALC_STATUS_DIVISION_BY_ZERO";
    case CALC_STATUS_INVALID_ARGUMENT:
        return "CALC_STATUS_INVALID_ARGUMENT";
    default:
        return "UNKNOWN_CALC_STATUS";
    }
}

static bool test_expect_calc_status_equal(const char *test_id,
                                          enum CalcStatus expected,
                                          enum CalcStatus actual)
{
    if (actual == expected)
    {
        return true;
    }

    fprintf(stderr,
            "%s FAILED: için beklenen durum = %s, gerceklesen = %s\n",
            test_id,
            calc_status_name(expected),
            calc_status_name(actual));
    return false;
}


static bool test_calc_01(const char *test_id)
{
    double result = 0.0;
    enum CalcStatus status = calculate(3.0, 4.0, CALC_OP_ADD, &result);

    if (!test_expect_calc_status_equal(test_id,

                                  CALC_STATUS_SUCCESS,
                                  status))
    {
        return false;
    }

    return test_expect_double_near(test_id, 7.0, result, TEST_DOUBLE_TOLERANCE);
}

static bool test_calc_02(const char *test_id)
{
    double result = 0.0;
    enum CalcStatus status = calculate(-2.5, 1.5, CALC_OP_ADD, &result);

    if (!test_expect_calc_status_equal(test_id,
                                  CALC_STATUS_SUCCESS,
                                  status))
    {
        return false;
    }

    return test_expect_double_near(test_id, -1.0, result, TEST_DOUBLE_TOLERANCE);
}

static bool test_calc_03(const char *test_id)
{
    double result = 0.0;
    enum CalcStatus status = calculate(3.0, 5.0, CALC_OP_SUBTRACT, &result);

    if (!test_expect_calc_status_equal(test_id,
                                  CALC_STATUS_SUCCESS,
                                  status))
    {
        return false;
    }

    return test_expect_double_near(test_id, -2.0, result, TEST_DOUBLE_TOLERANCE);
}
static bool test_calc_04(const char *test_id)
{
    double result = 0.0;
    enum CalcStatus status = calculate(-3.0, -5.0, CALC_OP_SUBTRACT, &result);

    if (!test_expect_calc_status_equal(test_id, CALC_STATUS_SUCCESS, status))
    {
        return false;
    }

    return test_expect_double_near(test_id, 2.0, result, TEST_DOUBLE_TOLERANCE);
}

static bool test_calc_05(const char *test_id)
{
    double result = 0.0;
    enum CalcStatus status = calculate(2.5, 4.0, CALC_OP_MULTIPLY, &result);

    if (!test_expect_calc_status_equal(test_id, CALC_STATUS_SUCCESS, status))
    {
        return false;
    }

    return test_expect_double_near(test_id, 10.0, result, TEST_DOUBLE_TOLERANCE);
}

static bool test_calc_06(const char *test_id)
{
    double result = 0.0;
    enum CalcStatus status = calculate(0.0, 7.25, CALC_OP_MULTIPLY, &result);

    if (!test_expect_calc_status_equal(test_id, CALC_STATUS_SUCCESS, status))
    {
        return false;
    }

    return test_expect_double_near(test_id, 0.0, result, TEST_DOUBLE_TOLERANCE);
}

static bool test_calc_07(const char *test_id)
{
    double result = 0.0;
    enum CalcStatus status = calculate(7.5, 2.5, CALC_OP_DIVIDE, &result);

    if (!test_expect_calc_status_equal(test_id, CALC_STATUS_SUCCESS, status))
    {
        return false;
    }

    return test_expect_double_near(test_id, 3.0, result, TEST_DOUBLE_TOLERANCE);
}

static bool test_calc_08(const char *test_id)
{
    const double sentinel = 42.0;
    double result = sentinel;
    enum CalcStatus status = calculate(12.0, 0.0, CALC_OP_DIVIDE, &result);

    if (!test_expect_calc_status_equal(test_id, CALC_STATUS_DIVISION_BY_ZERO, status))
    {
        return false;
    }

    return test_expect_double_near(test_id, sentinel, result, TEST_DOUBLE_TOLERANCE);
}

static bool test_calc_09(const char *test_id)
{
    const double sentinel = -13.0;
    double result = sentinel;
    enum CalcStatus status = calculate(3.0, 4.0, (enum CalcOp)99, &result);

    if (!test_expect_calc_status_equal(test_id, CALC_STATUS_UNSUPPORTED_OPERATION, status))
    {
        return false;
    }

    return test_expect_double_near(test_id, sentinel, result, TEST_DOUBLE_TOLERANCE);
}


static bool test_calc_10(const char *test_id)
{
    enum CalcStatus status = calculate(3.0, 4.0, CALC_OP_ADD, NULL);

    return test_expect_calc_status_equal(test_id,
                                    CALC_STATUS_INVALID_ARGUMENT,
                                    status);
}


int main(void)
{
    const struct TestCase tests[] = {
        {"CALC-01", test_calc_01},
        {"CALC-02", test_calc_02},
        {"CALC-03", test_calc_03},
        {"CALC-04", test_calc_04},
        {"CALC-05", test_calc_05},
        {"CALC-06", test_calc_06},
        {"CALC-07", test_calc_07},
        {"CALC-08", test_calc_08},
        {"CALC-09", test_calc_09},
        {"CALC-10", test_calc_10},
    };

    return test_run_cases(tests, sizeof(tests) / sizeof(tests[0]));
}
/* calc fix */
