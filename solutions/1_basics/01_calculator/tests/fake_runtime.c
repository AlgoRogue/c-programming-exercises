#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

static int getline_call_count = 0;

ssize_t test_getline(char **lineptr, size_t *capacity, FILE *stream)
{
    getline_call_count++;
    const char *fail_at_env = getenv("CALC_TEST_GETLINE_FAIL_AT");
    const char *error_env = getenv("CALC_TEST_GETLINE_ERROR");
    int fail_at = fail_at_env ? atoi(fail_at_env) : -1;

    if (fail_at > 0 && getline_call_count == fail_at) {
        if (error_env && strcmp(error_env, "memory") == 0) {
            errno = ENOMEM;
        } else if (error_env && strcmp(error_env, "io") == 0) {
            errno = EIO;
        } else {
            errno = EIO;
        }
        return -1;
    }
    return getline(lineptr, capacity, stream);
}

void test_free(void *pointer)
{
    const char *log_path = getenv("CALC_TEST_FREE_LOG");
    if (log_path) {
        FILE *f = fopen(log_path, "a");
        if (f) {
            fprintf(f, "free\n");
            fclose(f);
        }
    }
    free(pointer);
}
