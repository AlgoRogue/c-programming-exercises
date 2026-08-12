#include <stdio.h>
#include <stdlib.h>

#include "calculator.h"
#include "input.h"

static int run_single_operation(const char *first_text,
                                 const char *operation_text,
                                 const char *second_text,
                                 FILE *output,
                                 FILE *error)
{
    double a, b;
    enum CalcOp op;
    double result;

    if (parse_number(first_text, &a) != INPUT_STATUS_SUCCESS) {
        fprintf(error, "Hata: Geçersiz sayı.\n");
        return EXIT_FAILURE;
    }
    if (parse_operation(operation_text, &op) != INPUT_STATUS_SUCCESS) {
        fprintf(error, "Hata: Geçersiz işlem.\n");
        return EXIT_FAILURE;
    }
    if (parse_number(second_text, &b) != INPUT_STATUS_SUCCESS) {
        fprintf(error, "Hata: Geçersiz sayı.\n");
        return EXIT_FAILURE;
    }

    enum CalcStatus cs = calculate(a, b, op, &result);
    if (cs == CALC_STATUS_DIVISION_BY_ZERO) {
        fprintf(error, "Hata: Sıfıra bölme yapılamaz.\n");
        return EXIT_FAILURE;
    }
    if (cs == CALC_STATUS_UNSUPPORTED_OPERATION) {
        fprintf(error, "Hata: Desteklenmeyen işlem.\n");
        return EXIT_FAILURE;
    }
    if (cs == CALC_STATUS_INVALID_ARGUMENT || cs != CALC_STATUS_SUCCESS) {
        fprintf(error, "Hata: Geçersiz işlem.\n");
        return EXIT_FAILURE;
    }

    fprintf(output, "%.2f\n", result);
    return EXIT_SUCCESS;
}

int main(int argc, char *argv[])
{
    if (argc == 4) {
        return run_single_operation(argv[1], argv[2], argv[3], stdout, stderr);
    }
    fprintf(stderr, "Kullanım: %s [sayı işlem sayı]\n", argv[0]);
    return EXIT_FAILURE;
}
