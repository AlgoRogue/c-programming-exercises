#include "calculator.h"

enum CalcStatus calculate(double a, double b, enum CalcOp op, double *result)
{
    switch (op)
    {
    case TOPLA:
        *result = a + b;
        return CALC_BASARILI;
    case CIKAR:
        *result = a - b;
        return CALC_BASARILI;
    case CARP:
        *result = a * b;
        return CALC_BASARILI;
    case BOL:
        if (b == 0.0)
        {
            return CALC_SIFIRA_BOLME;
        }
        *result = a / b;
        return CALC_BASARILI;
    default:
        return CALC_DESTEKLENMEYEN_ISLEM;
    }
}
