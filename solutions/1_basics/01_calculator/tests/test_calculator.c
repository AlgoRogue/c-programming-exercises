#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>

#include "calculator.h"
#include "test_helpers.h"

// Kayan noktalı sonuçlar için mutlak karşılaştırma toleransı.
#define TEST_TOLERANCE 1e-9

typedef bool (*TestFunction)(const char *test_id);

struct TestCase
{
    const char *id;
    TestFunction run;
};

static bool test_calc_01(const char *test_id)
{
    double result = 0.0;
    enum CalcStatus status = calculate(3.0, 4.0, CALC_OP_ADD, &result);

    if (!test_expect_status_equal(test_id,
                                  CALC_STATUS_SUCCESS,
                                  status))
    {
        return false;
    }

    return test_expect_double_near(test_id, 7.0, result, TEST_TOLERANCE);
}

static bool test_calc_02(const char *test_id)
{
    double result = 0.0;
    enum CalcStatus status = calculate(-2.5, 1.5, CALC_OP_ADD, &result);

    if (!test_expect_status_equal(test_id,
                                  CALC_STATUS_SUCCESS,
                                  status))
    {
        return false;
    }

    return test_expect_double_near(test_id, -1.0, result, TEST_TOLERANCE);
}

static bool test_calc_03(const char *test_id)
{
    double result = 0.0;
    enum CalcStatus status = calculate(3.0, 5.0, CALC_OP_SUBTRACT, &result);

    if (!test_expect_status_equal(test_id,
                                  CALC_STATUS_SUCCESS,
                                  status))
    {
        return false;
    }

    return test_expect_double_near(test_id, -2.0, result, TEST_TOLERANCE);
}

int main(void)
{
    const struct TestCase tests[] = {
        {"CALC-01", test_calc_01},
        {"CALC-02", test_calc_02},
        {"CALC-03", test_calc_03},
    };
    const size_t test_count = sizeof(tests) / sizeof(tests[0]);
    size_t failure_count = 0;

    for (size_t index = 0; index < test_count; ++index)
    {
        if (tests[index].run(tests[index].id))
        {
            printf("%s PASSED\n", tests[index].id);
        }
        else
        {
            ++failure_count;
        }
    }

    printf("\n%zu test çalıştırıldı: %zu başarılı, %zu başarısız.\n",
           test_count,
           test_count - failure_count,
           failure_count);

    return failure_count == 0 ? 0 : 1;
}
