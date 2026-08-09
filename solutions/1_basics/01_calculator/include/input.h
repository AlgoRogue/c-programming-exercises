#ifndef INPUT_H
#define INPUT_H

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

enum InputStatus parse_number(const char *text, double *output);
enum InputStatus parse_operation(const char *text, enum CalcOp *output);


#endif // INPUT_H
