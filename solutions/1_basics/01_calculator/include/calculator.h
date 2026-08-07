#ifndef CALCULATOR_H
#define CALCULATOR_H

enum CalcOp
{
    TOPLA,
    CIKAR,
    CARP,
    BOL
};

enum CalcStatus
{
    CALC_BASARILI,
    CALC_DESTEKLENMEYEN_ISLEM,
    CALC_SIFIRA_BOLME
};

// Hesaplama fonksiyonumuzun sözleşmesi (prototipi)
enum CalcStatus calculate(double a, double b, enum CalcOp op, double *result);

#endif // CALCULATOR_H