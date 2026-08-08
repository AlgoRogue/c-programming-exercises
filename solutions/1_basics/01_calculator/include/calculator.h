#ifndef CALCULATOR_H
#define CALCULATOR_H

enum CalcOp
{
    CALC_OP_ADD,
    CALC_OP_SUBTRACT,
    CALC_OP_MULTIPLY,
    CALC_OP_DIVIDE
};

enum CalcStatus
{
    CALC_STATUS_SUCCESS,
    CALC_STATUS_UNSUPPORTED_OPERATION,
    CALC_STATUS_DIVISION_BY_ZERO
};

// Hesaplama fonksiyonumuzun sözleşmesi (prototipi)
enum CalcStatus calculate(double a, double b, enum CalcOp op, double *result);

#endif // CALCULATOR_H