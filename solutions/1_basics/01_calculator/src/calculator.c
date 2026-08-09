#include <stddef.h>

#include "calculator.h"

enum CalcStatus calculate(double a, double b, enum CalcOp op, double *result)
{
    if (result == NULL)
    {
        return CALC_STATUS_INVALID_ARGUMENT;
    }

    switch (op)
    {
    case CALC_OP_ADD:
        *result = a + b;
        return CALC_STATUS_SUCCESS;
    case CALC_OP_SUBTRACT:
        *result = a - b;
        return CALC_STATUS_SUCCESS;
    case CALC_OP_MULTIPLY:
        *result = a * b;
        return CALC_STATUS_SUCCESS;
    case CALC_OP_DIVIDE:
        if (b == 0.0)
        {
            return CALC_STATUS_DIVISION_BY_ZERO;
        }
        *result = a / b;
        return CALC_STATUS_SUCCESS;
    default:
        return CALC_STATUS_UNSUPPORTED_OPERATION;
    }
}
/* calc fix */
