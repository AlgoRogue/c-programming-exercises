#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

static enum InputStatus prompt_for_number(FILE *input,
                                          FILE *output,
                                          FILE *error,
                                          const char *prompt,
                                          char **buffer,
                                          size_t *capacity,
                                          double *value)
{
    fprintf(output, "%s", prompt);
    fflush(output);
    enum InputStatus s = read_line(input, buffer, capacity);
    if (s == INPUT_STATUS_SUCCESS) {
        s = parse_number(*buffer, value);
        if (s == INPUT_STATUS_INVALID_INPUT) {
            fprintf(error, "Hata: Geçersiz sayı.\n");
            return INPUT_STATUS_INVALID_INPUT;
        }
    }
    return s;
}

static enum InputStatus prompt_for_operation(FILE *input,
                                              FILE *output,
                                              FILE *error,
                                              char **buffer,
                                              size_t *capacity,
                                              enum CalcOp *operation)
{
    fprintf(output, "İşlem (+, -, *, x, /): ");
    fflush(output);
    enum InputStatus s = read_line(input, buffer, capacity);
    if (s == INPUT_STATUS_SUCCESS) {
        s = parse_operation(*buffer, operation);
        if (s == INPUT_STATUS_INVALID_INPUT) {
            fprintf(error, "Hata: Geçersiz işlem.\n");
            return INPUT_STATUS_INVALID_INPUT;
        }
    }
    return s;
}

static enum InputStatus prompt_for_continue(FILE *input,
                                              FILE *output,
                                              FILE *error,
                                              char **buffer,
                                              size_t *capacity,
                                              enum ContinueChoice *choice)
{
    fprintf(output, "Devam etmek için 'e', çıkmak için 'h': ");
    fflush(output);
    enum InputStatus s = read_line(input, buffer, capacity);
    if (s == INPUT_STATUS_SUCCESS) {
        s = parse_continue_choice(*buffer, choice);
        if (s == INPUT_STATUS_INVALID_INPUT) {
            fprintf(error, "Hata: Geçersiz devam seçimi.\n");
            return INPUT_STATUS_INVALID_INPUT;
        }
    }
    return s;
}

static int run_interactive(FILE *input, FILE *output, FILE *error)
{
    char *buffer = NULL;
    size_t capacity = 0;
    int exit_code = EXIT_FAILURE;

    while (1) {
        double first = 0, second = 0;
        enum CalcOp op = CALC_OP_ADD;
        double result = 0;

        enum InputStatus s = prompt_for_number(input, output, error,
                                               "Birinci sayı: ",
                                               &buffer, &capacity, &first);
        if (s == INPUT_STATUS_END_OF_FILE) {
            exit_code = EXIT_SUCCESS;
            goto cleanup;
        }
        if (s == INPUT_STATUS_INVALID_INPUT) {
            continue;
        }
        if (s != INPUT_STATUS_SUCCESS) {
            exit_code = EXIT_FAILURE;
            goto cleanup;
        }

        s = prompt_for_operation(input, output, error,
                                  &buffer, &capacity, &op);
        if (s == INPUT_STATUS_END_OF_FILE) {
            exit_code = EXIT_SUCCESS;
            goto cleanup;
        }
        if (s == INPUT_STATUS_INVALID_INPUT) {
            continue;
        }
        if (s != INPUT_STATUS_SUCCESS) {
            exit_code = EXIT_FAILURE;
            goto cleanup;
        }

        s = prompt_for_number(input, output, error,
                               "İkinci sayı: ",
                               &buffer, &capacity, &second);
        if (s == INPUT_STATUS_END_OF_FILE) {
            exit_code = EXIT_SUCCESS;
            goto cleanup;
        }
        if (s == INPUT_STATUS_INVALID_INPUT) {
            continue;
        }
        if (s != INPUT_STATUS_SUCCESS) {
            exit_code = EXIT_FAILURE;
            goto cleanup;
        }

        enum CalcStatus cs = calculate(first, second, op, &result);
        if (cs == CALC_STATUS_DIVISION_BY_ZERO) {
            fprintf(error, "Hata: Sıfıra bölme yapılamaz.\n");
            continue;
        }
        if (cs == CALC_STATUS_UNSUPPORTED_OPERATION) {
            fprintf(error, "Hata: Desteklenmeyen işlem.\n");
            exit_code = EXIT_FAILURE;
            goto cleanup;
        }
        if (cs == CALC_STATUS_INVALID_ARGUMENT || cs != CALC_STATUS_SUCCESS) {
            fprintf(error, "Hata: Geçersiz işlem.\n");
            exit_code = EXIT_FAILURE;
            goto cleanup;
        }

        fprintf(output, "Sonuç: %.2f\n", result);

        enum ContinueChoice choice = CONTINUE_CHOICE_CONTINUE;
        s = prompt_for_continue(input, output, error,
                                 &buffer, &capacity, &choice);
        if (s == INPUT_STATUS_END_OF_FILE) {
            exit_code = EXIT_SUCCESS;
            goto cleanup;
        }
        if (s == INPUT_STATUS_INVALID_INPUT) {
            continue;
        }
        if (s != INPUT_STATUS_SUCCESS) {
            exit_code = EXIT_FAILURE;
            goto cleanup;
        }
        if (choice == CONTINUE_CHOICE_EXIT) {
            exit_code = EXIT_SUCCESS;
            goto cleanup;
        }
        if (choice == CONTINUE_CHOICE_CONTINUE) {
            continue;
        }
    }

cleanup:
    free(buffer);
    return exit_code;
}

int main(int argc, char *argv[])
{
    if (argc == 4) {
        return run_single_operation(argv[1], argv[2], argv[3], stdout, stderr);
    }
    if (argc == 1) {
        return run_interactive(stdin, stdout, stderr);
    }
    fprintf(stderr, "Kullanım: %s [sayı işlem sayı]\n", argv[0]);
    return EXIT_FAILURE;
}
