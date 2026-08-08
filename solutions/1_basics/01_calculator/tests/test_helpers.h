#ifndef TEST_HELPERS_H
#define TEST_HELPERS_H

#include <math.h>
#include <stdbool.h>
#include <stdio.h>

#include "calculator.h"

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
    default:
        return "UNKNOWN_CALC_STATUS";
    }
}

static inline bool test_expect_status_equal(const char *test_id,
                                            enum CalcStatus expected,
                                            enum CalcStatus actual)
{
    if (actual == expected)
    {
        return true;
    }

    fprintf(
        stderr,
        "%s FAILED: için beklenen durum = %s, gerceklesen = %s\n",
        test_id,
        calc_status_name(expected),
        calc_status_name(actual)
    );
    return false;
}

static inline bool test_expect_double_near(const char *test_id,
                                           double expected,
                                           double actual,
                                           double tolerance)
{
    if (isfinite(actual) &&
        isfinite(expected) &&
        fabs(actual - expected) <= tolerance)
    {
        return true;
    }

    fprintf(stderr,
            "%s FAILED: için beklenen sonuc = %.17g, gerceklesen = %.17g, "
            "tolerans=%.17g\n",
            test_id,
            expected,
            actual,
            tolerance);
    return false;
}

#endif // TEST_HELPERS_H
