#include "input.h"

#include <stdbool.h>
#include <ctype.h>
#include <errno.h>
#include <stdlib.h>

static const unsigned char *skip_whitespace(const unsigned char *cursor)
{
    while (isspace(*cursor))
    {
        ++cursor;
    }

    return cursor;
}

static enum InputStatus parse_single_symbol(const char *text, char *output)
{
    const unsigned char *cursor =
        skip_whitespace((const unsigned char *)text);

    if (*cursor == '\0')
    {
        return INPUT_STATUS_INVALID_INPUT;
    }

    char symbol = (char)*cursor;
    cursor = skip_whitespace(cursor + 1);

    if (*cursor != '\0')
    {
        return INPUT_STATUS_INVALID_INPUT;
    }

    *output = symbol;
    return INPUT_STATUS_SUCCESS;
}
enum InputStatus parse_number(const char *text, double *output)
{
    if (text == NULL || output == NULL)
    {
        return INPUT_STATUS_INVALID_ARGUMENT;
    }

    const unsigned char *cursor =
        skip_whitespace((const unsigned char *)text);

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
    cursor = skip_whitespace(cursor);

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

    char symbol;
    enum InputStatus status = parse_single_symbol(text, &symbol);
    if (status != INPUT_STATUS_SUCCESS)
    {
        return status;
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

enum InputStatus parse_continue_choice(const char *text,
                                       enum ContinueChoice *output)
{
    if (text == NULL || output == NULL)
    {
        return INPUT_STATUS_INVALID_ARGUMENT;
    }

    char symbol;
    enum InputStatus status = parse_single_symbol(text, &symbol);
    if (status != INPUT_STATUS_SUCCESS)
    {
        return status;
    }

    enum ContinueChoice choice;
    switch (symbol)
    {
    case 'e':
        choice = CONTINUE_CHOICE_CONTINUE;
        break;
    case 'h':
        choice = CONTINUE_CHOICE_EXIT;
        break;
    default:
        return INPUT_STATUS_INVALID_INPUT;
    }

    *output = choice;
    return INPUT_STATUS_SUCCESS;
}

enum InputStatus read_line(FILE *stream,
                           char **buffer,
                           size_t *capacity)
{
    if (stream == NULL || buffer == NULL || capacity == NULL)
    {
        return INPUT_STATUS_INVALID_ARGUMENT;
    }
    errno = 0;
    ssize_t n = getline(buffer, capacity, stream);
    if (n >= 0)
    {
        return INPUT_STATUS_SUCCESS;
    }
    if (errno == ENOMEM)
    {
        return INPUT_STATUS_MEMORY_ERROR;
    }

    if (feof(stream))
    {
        return INPUT_STATUS_END_OF_FILE;
    }

    return INPUT_STATUS_IO_ERROR;
}
