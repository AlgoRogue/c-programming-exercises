#include "input.h"

#include <errno.h>
#include <stdlib.h>

enum InputStatus parse_number(const char *text, double *output)
{
    if (text == NULL || output == NULL)
    {
        return INPUT_STATUS_INVALID_ARGUMENT;
    }

    char *end = NULL;
    errno = 0;
    double value = strtod(text, &end);

    if (end == text || *end != '\0' || errno == ERANGE)
    {
        return INPUT_STATUS_INVALID_INPUT;
    }

    *output = value;
    return INPUT_STATUS_SUCCESS;
}
