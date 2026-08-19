#include <stdlib.h>

#include "dynamic_array.h"

#define DYN_ARRAY_DEFAULT_GROWTH_CAPACITY 4

enum DynArrayStatus dynamic_array_init(struct DynamicArray *arr, size_t initial_capacity)
{
    if (arr == NULL)
    {
        return DYN_ARRAY_STATUS_INVALID_ARGUMENT;
    }

    if (initial_capacity == 0)
    {
        arr->data = NULL;
        arr->size = 0;
        arr->capacity = 0;
        return DYN_ARRAY_STATUS_SUCCESS;
    }

    int *data = malloc(initial_capacity * sizeof(int));
    if (data == NULL)
    {
        return DYN_ARRAY_STATUS_ALLOCATION_FAILURE;
    }

    arr->data = data;
    arr->size = 0;
    arr->capacity = initial_capacity;
    return DYN_ARRAY_STATUS_SUCCESS;
}

enum DynArrayStatus dynamic_array_push_back(struct DynamicArray *arr, int value)
{
    if (arr == NULL)
    {
        return DYN_ARRAY_STATUS_INVALID_ARGUMENT;
    }

    if (arr->size == arr->capacity)
    {
        size_t new_capacity = arr->capacity == 0
            ? DYN_ARRAY_DEFAULT_GROWTH_CAPACITY
            : arr->capacity * 2;

        int *new_data = realloc(arr->data, new_capacity * sizeof(int));
        if (new_data == NULL)
        {
            return DYN_ARRAY_STATUS_ALLOCATION_FAILURE;
        }

        arr->data = new_data;
        arr->capacity = new_capacity;
    }

    arr->data[arr->size] = value;
    ++arr->size;
    return DYN_ARRAY_STATUS_SUCCESS;
}

enum DynArrayStatus dynamic_array_remove_at(struct DynamicArray *arr, size_t index)
{
    if (arr == NULL)
    {
        return DYN_ARRAY_STATUS_INVALID_ARGUMENT;
    }

    if (index >= arr->size)
    {
        return DYN_ARRAY_STATUS_OUT_OF_BOUNDS;
    }

    for (size_t i = index; i + 1 < arr->size; ++i)
    {
        arr->data[i] = arr->data[i + 1];
    }

    --arr->size;
    return DYN_ARRAY_STATUS_SUCCESS;
}

enum DynArrayStatus dynamic_array_get(const struct DynamicArray *arr, size_t index, int *out_value)
{
    if (arr == NULL || out_value == NULL)
    {
        return DYN_ARRAY_STATUS_INVALID_ARGUMENT;
    }

    if (index >= arr->size)
    {
        return DYN_ARRAY_STATUS_OUT_OF_BOUNDS;
    }

    *out_value = arr->data[index];
    return DYN_ARRAY_STATUS_SUCCESS;
}

size_t dynamic_array_size(const struct DynamicArray *arr)
{
    if (arr == NULL)
    {
        return 0;
    }

    return arr->size;
}
