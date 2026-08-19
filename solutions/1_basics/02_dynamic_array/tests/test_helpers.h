#ifndef TEST_HELPERS_H
#define TEST_HELPERS_H

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

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

static inline bool test_expect_int_equal(const char *test_id,
                                         int expected,
                                         int actual)
{
    if (actual == expected)
    {
        return true;
    }

    fprintf(stderr,
            "%s FAILED: beklenen = %d, gerceklesen = %d\n",
            test_id,
            expected,
            actual);
    return false;
}

static inline bool test_expect_size_equal(const char *test_id,
                                          size_t expected,
                                          size_t actual)
{
    if (actual == expected)
    {
        return true;
    }

    fprintf(stderr,
            "%s FAILED: beklenen = %zu, gerceklesen = %zu\n",
            test_id,
            expected,
            actual);
    return false;
}

#endif // TEST_HELPERS_H
