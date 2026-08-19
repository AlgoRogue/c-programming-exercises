#include <stdbool.h>
#include <stdio.h>

#include "dynamic_array.h"
#include "test_helpers.h"

static const char *dyn_array_status_name(enum DynArrayStatus status)
{
    switch (status)
    {
    case DYN_ARRAY_STATUS_SUCCESS:
        return "DYN_ARRAY_STATUS_SUCCESS";
    case DYN_ARRAY_STATUS_OUT_OF_BOUNDS:
        return "DYN_ARRAY_STATUS_OUT_OF_BOUNDS";
    case DYN_ARRAY_STATUS_ALLOCATION_FAILURE:
        return "DYN_ARRAY_STATUS_ALLOCATION_FAILURE";
    case DYN_ARRAY_STATUS_INVALID_ARGUMENT:
        return "DYN_ARRAY_STATUS_INVALID_ARGUMENT";
    default:
        return "UNKNOWN_DYN_ARRAY_STATUS";
    }
}

static bool test_expect_status_equal(const char *test_id,
                                     enum DynArrayStatus expected,
                                     enum DynArrayStatus actual)
{
    if (actual == expected)
    {
        return true;
    }

    fprintf(stderr,
            "%s FAILED: beklenen durum = %s, gerceklesen = %s\n",
            test_id,
            dyn_array_status_name(expected),
            dyn_array_status_name(actual));
    return false;
}

static bool test_dynarr_01(const char *test_id)
{
    struct DynamicArray arr;
    enum DynArrayStatus status = dynamic_array_init(&arr, 4);

    if (!test_expect_status_equal(test_id, DYN_ARRAY_STATUS_SUCCESS, status))
    {
        return false;
    }
    if (!test_expect_size_equal(test_id, 0, arr.size))
    {
        return false;
    }
    return test_expect_size_equal(test_id, 4, arr.capacity);
}

static bool test_dynarr_02(const char *test_id)
{
    struct DynamicArray arr;
    enum DynArrayStatus status = dynamic_array_init(&arr, 0);

    if (!test_expect_status_equal(test_id, DYN_ARRAY_STATUS_SUCCESS, status))
    {
        return false;
    }
    if (!test_expect_size_equal(test_id, 0, arr.size))
    {
        return false;
    }
    return test_expect_size_equal(test_id, 0, arr.capacity);
}

static bool test_dynarr_03(const char *test_id)
{
    enum DynArrayStatus status = dynamic_array_init(NULL, 4);

    return test_expect_status_equal(test_id, DYN_ARRAY_STATUS_INVALID_ARGUMENT, status);
}

static bool test_dynarr_04(const char *test_id)
{
    struct DynamicArray arr;
    dynamic_array_init(&arr, 2);

    enum DynArrayStatus status = DYN_ARRAY_STATUS_SUCCESS;
    for (int value = 10; value <= 50 && status == DYN_ARRAY_STATUS_SUCCESS; value += 10)
    {
        status = dynamic_array_push_back(&arr, value);
    }

    if (!test_expect_status_equal(test_id, DYN_ARRAY_STATUS_SUCCESS, status))
    {
        return false;
    }
    if (!test_expect_size_equal(test_id, 5, arr.size))
    {
        return false;
    }
    if (arr.capacity < arr.size)
    {
        fprintf(stderr, "%s FAILED: kapasite (%zu) eleman sayisindan (%zu) kucuk\n",
                test_id, arr.capacity, arr.size);
        return false;
    }

    const int expected[] = {10, 20, 30, 40, 50};
    for (size_t index = 0; index < 5; ++index)
    {
        if (!test_expect_int_equal(test_id, expected[index], arr.data[index]))
        {
            return false;
        }
    }
    return true;
}

static bool test_dynarr_05(const char *test_id)
{
    enum DynArrayStatus status = dynamic_array_push_back(NULL, 1);

    return test_expect_status_equal(test_id, DYN_ARRAY_STATUS_INVALID_ARGUMENT, status);
}

static bool test_dynarr_06(const char *test_id)
{
    struct DynamicArray arr;
    dynamic_array_init(&arr, 0);

    enum DynArrayStatus status = dynamic_array_push_back(&arr, 7);

    if (!test_expect_status_equal(test_id, DYN_ARRAY_STATUS_SUCCESS, status))
    {
        return false;
    }
    if (!test_expect_size_equal(test_id, 1, arr.size))
    {
        return false;
    }
    return test_expect_int_equal(test_id, 7, arr.data[0]);
}

static bool test_dynarr_07(const char *test_id)
{
    struct DynamicArray arr;
    dynamic_array_init(&arr, 2);
    dynamic_array_push_back(&arr, 42);

    int value = 0;
    enum DynArrayStatus status = dynamic_array_get(&arr, 0, &value);

    if (!test_expect_status_equal(test_id, DYN_ARRAY_STATUS_SUCCESS, status))
    {
        return false;
    }
    return test_expect_int_equal(test_id, 42, value);
}

static bool test_dynarr_08(const char *test_id)
{
    struct DynamicArray arr;
    dynamic_array_init(&arr, 2);
    dynamic_array_push_back(&arr, 1);

    int value = 0;
    enum DynArrayStatus status = dynamic_array_get(&arr, 1, &value);

    return test_expect_status_equal(test_id, DYN_ARRAY_STATUS_OUT_OF_BOUNDS, status);
}

static bool test_dynarr_09(const char *test_id)
{
    int value = 0;
    enum DynArrayStatus status = dynamic_array_get(NULL, 0, &value);

    return test_expect_status_equal(test_id, DYN_ARRAY_STATUS_INVALID_ARGUMENT, status);
}

static bool test_dynarr_10(const char *test_id)
{
    struct DynamicArray arr;
    dynamic_array_init(&arr, 2);
    dynamic_array_push_back(&arr, 1);

    enum DynArrayStatus status = dynamic_array_get(&arr, 0, NULL);

    return test_expect_status_equal(test_id, DYN_ARRAY_STATUS_INVALID_ARGUMENT, status);
}

static bool test_dynarr_11(const char *test_id)
{
    struct DynamicArray arr;
    dynamic_array_init(&arr, 2);
    dynamic_array_push_back(&arr, 1);
    dynamic_array_push_back(&arr, 2);
    dynamic_array_push_back(&arr, 3);

    return test_expect_size_equal(test_id, 3, dynamic_array_size(&arr));
}

static bool test_dynarr_12(const char *test_id)
{
    return test_expect_size_equal(test_id, 0, dynamic_array_size(NULL));
}

static bool test_dynarr_13(const char *test_id)
{
    struct DynamicArray arr;
    dynamic_array_init(&arr, 4);
    dynamic_array_push_back(&arr, 1);
    dynamic_array_push_back(&arr, 2);
    dynamic_array_push_back(&arr, 3);

    enum DynArrayStatus status = dynamic_array_remove_at(&arr, 1);

    if (!test_expect_status_equal(test_id, DYN_ARRAY_STATUS_SUCCESS, status))
    {
        return false;
    }
    if (!test_expect_size_equal(test_id, 2, arr.size))
    {
        return false;
    }
    if (!test_expect_int_equal(test_id, 1, arr.data[0]))
    {
        return false;
    }
    return test_expect_int_equal(test_id, 3, arr.data[1]);
}

static bool test_dynarr_14(const char *test_id)
{
    struct DynamicArray arr;
    dynamic_array_init(&arr, 2);
    dynamic_array_push_back(&arr, 1);

    enum DynArrayStatus status = dynamic_array_remove_at(&arr, 1);

    return test_expect_status_equal(test_id, DYN_ARRAY_STATUS_OUT_OF_BOUNDS, status);
}

static bool test_dynarr_15(const char *test_id)
{
    enum DynArrayStatus status = dynamic_array_remove_at(NULL, 0);

    return test_expect_status_equal(test_id, DYN_ARRAY_STATUS_INVALID_ARGUMENT, status);
}

static bool test_dynarr_16(const char *test_id)
{
    struct DynamicArray arr;
    dynamic_array_init(&arr, 2);
    dynamic_array_push_back(&arr, 1);
    dynamic_array_push_back(&arr, 2);

    enum DynArrayStatus status = dynamic_array_remove_at(&arr, 1);

    if (!test_expect_status_equal(test_id, DYN_ARRAY_STATUS_SUCCESS, status))
    {
        return false;
    }
    if (!test_expect_size_equal(test_id, 1, arr.size))
    {
        return false;
    }
    return test_expect_int_equal(test_id, 1, arr.data[0]);
}

static bool test_dynarr_17(const char *test_id)
{
    struct DynamicArray arr;
    dynamic_array_init(&arr, 4);
    dynamic_array_push_back(&arr, 1);
    dynamic_array_push_back(&arr, 2);

    dynamic_array_free(&arr);

    if (arr.data != NULL)
    {
        fprintf(stderr, "%s FAILED: data NULL olmali\n", test_id);
        return false;
    }
    if (!test_expect_size_equal(test_id, 0, arr.size))
    {
        return false;
    }
    return test_expect_size_equal(test_id, 0, arr.capacity);
}

static bool test_dynarr_18(const char *test_id)
{
    struct DynamicArray arr;
    dynamic_array_init(&arr, 0);

    dynamic_array_free(&arr);

    if (arr.data != NULL)
    {
        fprintf(stderr, "%s FAILED: data NULL olmali\n", test_id);
        return false;
    }
    return test_expect_size_equal(test_id, 0, arr.capacity);
}

static bool test_dynarr_19(const char *test_id)
{
    (void)test_id;
    dynamic_array_free(NULL);
    return true;
}

int main(void)
{
    const struct TestCase tests[] = {
        {"DYNARR-01", test_dynarr_01},
        {"DYNARR-02", test_dynarr_02},
        {"DYNARR-03", test_dynarr_03},
        {"DYNARR-04", test_dynarr_04},
        {"DYNARR-05", test_dynarr_05},
        {"DYNARR-06", test_dynarr_06},
        {"DYNARR-07", test_dynarr_07},
        {"DYNARR-08", test_dynarr_08},
        {"DYNARR-09", test_dynarr_09},
        {"DYNARR-10", test_dynarr_10},
        {"DYNARR-11", test_dynarr_11},
        {"DYNARR-12", test_dynarr_12},
        {"DYNARR-13", test_dynarr_13},
        {"DYNARR-14", test_dynarr_14},
        {"DYNARR-15", test_dynarr_15},
        {"DYNARR-16", test_dynarr_16},
        {"DYNARR-17", test_dynarr_17},
        {"DYNARR-18", test_dynarr_18},
        {"DYNARR-19", test_dynarr_19},
    };

    return test_run_cases(tests, sizeof(tests) / sizeof(tests[0]));
}
