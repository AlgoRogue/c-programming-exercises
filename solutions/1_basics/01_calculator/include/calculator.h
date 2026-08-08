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
    CALC_STATUS_DIVISION_BY_ZERO,
    CALC_STATUS_INVALID_ARGUMENT
};

/**
 * @brief Verilen iki sayıya aritmetik işlem uygular.
 *
 * @param a Birinci işlem değeri.
 * @param b İkinci işlem değeri.
 * @param op Uygulanacak aritmetik işlem.
 * @param result Başarılı hesaplama sonucunun yazılacağı işaretçi; `NULL`
 *               verildiğinde `CALC_STATUS_INVALID_ARGUMENT` döner.
 *
 * @return Hesaplama işleminin durum kodu.
 */
enum CalcStatus calculate(double a, double b, enum CalcOp op, double *result);

#endif // CALCULATOR_H