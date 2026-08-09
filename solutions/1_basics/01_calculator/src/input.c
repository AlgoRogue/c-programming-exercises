#include "input.h"

#include <stdbool.h>
#include <ctype.h>
#include <errno.h>
#include <stdlib.h>

enum InputStatus parse_number(const char *text, double *output)
{
    if (text == NULL || output == NULL)
    {
        return INPUT_STATUS_INVALID_ARGUMENT;
    }

    const unsigned char *cursor = (const unsigned char *)text;
    while (isspace(*cursor))
    {
        ++cursor;
    }

    const char *number_start = (const char *)cursor;
    if (*cursor == '+' || *cursor == '-')
    {
        ++cursor;
    }

    bool has_digit = false;
    while (*cursor >= '0' && *cursor <= '9')
    {
        has_digit = true;
        ++cursor;
    }

    if (*cursor == '.')
    {
        ++cursor;
        while (*cursor >= '0' && *cursor <= '9')
        {
            has_digit = true;
            ++cursor;
        }
    }

    if (!has_digit)
    {
        return INPUT_STATUS_INVALID_INPUT;
    }

    const char *number_end = (const char *)cursor;
    while (isspace(*cursor))
    {
        ++cursor;
    }

    if (*cursor != '\0')
    {
        return INPUT_STATUS_INVALID_INPUT;
    }

    char *end = NULL;
    errno = 0;
    double value = strtod(number_start, &end);

    if (end != number_end || errno == ERANGE)
    {
        return INPUT_STATUS_INVALID_INPUT;
    }

    *output = value;
    return INPUT_STATUS_SUCCESS;
}

enum InputStatus parse_operation(const char *text, enum CalcOp *output)
{
    if (text == NULL || output == NULL)
    {
        return INPUT_STATUS_INVALID_ARGUMENT;
    }

    const unsigned char *cursor = (const unsigned char *)text;
    while (isspace(*cursor))
    {
        ++cursor;
    }

    if (*cursor == '\0')
    {
        return INPUT_STATUS_INVALID_INPUT;
    }

    char symbol = (char)*cursor;
    ++cursor;

    while (isspace(*cursor))
    {
        ++cursor;
    }

    if (*cursor != '\0')
    {
        return INPUT_STATUS_INVALID_INPUT;
    }

    enum CalcOp operation;
    switch (symbol)
    {
    case '+':
        operation = CALC_OP_ADD;
        break;
    case '-':
        operation = CALC_OP_SUBTRACT;
        break;
    case '*':
    case 'x':
        operation = CALC_OP_MULTIPLY;
        break;
    case '/':
        operation = CALC_OP_DIVIDE;
        break;
    default:
        return INPUT_STATUS_INVALID_INPUT;
    }

    *output = operation;
    return INPUT_STATUS_SUCCESS;
}
