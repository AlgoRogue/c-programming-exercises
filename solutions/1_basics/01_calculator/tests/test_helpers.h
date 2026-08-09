#ifndef TEST_HELPERS_H
#define TEST_HELPERS_H

#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

#define TEST_DOUBLE_TOLERANCE 1e-9

typedef bool (*TestFunction)(const char *test_id);

struct TestCase
{
    const char *id;
    TestFunction run;
};

static inline int test_run_cases(const struct TestCase *tests,
                                 size_t test_count)
{
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
