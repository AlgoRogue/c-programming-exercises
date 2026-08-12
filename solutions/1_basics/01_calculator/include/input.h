#ifndef INPUT_H
#define INPUT_H

#include <stddef.h>
#include <stdio.h>
#include "calculator.h"

enum InputStatus
{
    INPUT_STATUS_SUCCESS,
    INPUT_STATUS_INVALID_INPUT,
    INPUT_STATUS_END_OF_FILE,
    INPUT_STATUS_IO_ERROR,
    INPUT_STATUS_MEMORY_ERROR,
    INPUT_STATUS_INVALID_ARGUMENT
};

enum ContinueChoice
{
    CONTINUE_CHOICE_CONTINUE,
    CONTINUE_CHOICE_EXIT
};

enum InputStatus parse_number(const char *text, double *output);
enum InputStatus parse_operation(const char *text, enum CalcOp *output);
enum InputStatus parse_continue_choice(const char *text,
                                       enum ContinueChoice *output);
enum InputStatus read_line(FILE *stream,
                           char **buffer,
                           size_t *capacity);

#endif // INPUT_H
