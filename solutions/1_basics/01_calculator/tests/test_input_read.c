#include <errno.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include "input.h"
#include "test_helpers.h"

enum FakeGetlineMode
{
    FAKE_GETLINE_SUCCESS,
    FAKE_GETLINE_EOF,
    FAKE_GETLINE_IO_ERROR,
    FAKE_GETLINE_MEMORY_ERROR
};

static enum FakeGetlineMode current_mode;
static int call_counter;

static void reset_fake(enum FakeGetlineMode mode)
{
    current_mode = mode;
    call_counter = 0;
}
ssize_t test_getline(char **lineptr, size_t *capacity, FILE *stream)
{
    (void)stream;
    ++call_counter;
    if (current_mode == FAKE_GETLINE_SUCCESS)
    {
        char text[83];
        memset(text, '0', 80);
        text[80] = '1';
        text[81] = '\n';
        text[82] = '\0';
        char *buf = realloc(*lineptr, sizeof(text));
        if (!buf)
        {
            errno = ENOMEM;
            return -1;
        }
        *lineptr = buf;
        memcpy(*lineptr, text, sizeof(text));
        *capacity = sizeof(text);
        return 82;
    }
    else if (current_mode == FAKE_GETLINE_EOF)
    {
        rewind(stream);
        fgetc(stream); // set EOF on empty stream
        errno = 0;
        return -1;
    }
    else if (current_mode == FAKE_GETLINE_IO_ERROR)
    {
        errno = EIO;
        return -1;
    }
    else if (current_mode == FAKE_GETLINE_MEMORY_ERROR)
    {
        errno = ENOMEM;
        return -1;
    }
    return -1;
}

static bool test_expect_input_status_equal(const char *test_id,
                                            enum InputStatus expected,
                                            enum InputStatus actual)
{
    if (expected == actual)
    {
        return true;
    }
    fprintf(stderr,
            "%s FAILED: beklenen durum = %d, gerceklesen = %d\n",
            test_id,
            (int)expected,
            (int)actual);
    return false;
}

static bool test_line_01(const char *test_id)
{
    reset_fake(FAKE_GETLINE_SUCCESS);
    FILE *stream = tmpfile();
    char *buffer = NULL;
    size_t capacity = 0;
    enum InputStatus status = read_line(stream, &buffer, &capacity);
    bool ok = test_expect_input_status_equal(test_id,
                                             INPUT_STATUS_SUCCESS,
                                             status);
    if (buffer && ok)
    {
        ok = ok && (strlen(buffer) == 82);
        ok = ok && (capacity == 83);
        ok = ok && (buffer[80] == '1');
        ok = ok && (buffer[81] == '\n');
        ok = ok && (buffer[82] == '\0');
    }
    free(buffer);
    fclose(stream);
    return ok;
}

static bool test_line_02(const char *test_id)
{
    reset_fake(FAKE_GETLINE_EOF);
    FILE *stream = tmpfile();
    char *buffer = NULL;
    size_t capacity = 0;
    enum InputStatus status = read_line(stream, &buffer, &capacity);
    bool ok = test_expect_input_status_equal(test_id,
                                             INPUT_STATUS_END_OF_FILE,
                                             status);
    free(buffer);
    fclose(stream);
    return ok;
}

static bool test_line_03(const char *test_id)
{
    reset_fake(FAKE_GETLINE_IO_ERROR);
    FILE *stream = tmpfile();
    char *buffer = NULL;
    size_t capacity = 0;
    enum InputStatus status = read_line(stream, &buffer, &capacity);
    bool ok = test_expect_input_status_equal(test_id,
                                             INPUT_STATUS_IO_ERROR,
                                             status);
    free(buffer);
    fclose(stream);
    return ok;
}

static bool test_line_04(const char *test_id)
{
    reset_fake(FAKE_GETLINE_MEMORY_ERROR);
    FILE *stream = tmpfile();
    char *buffer = NULL;
    size_t capacity = 0;
    enum InputStatus status = read_line(stream, &buffer, &capacity);
    bool ok = test_expect_input_status_equal(test_id,
                                             INPUT_STATUS_MEMORY_ERROR,
                                             status);
    free(buffer);
    fclose(stream);
    return ok;
}

static bool test_line_05(const char *test_id)
{
    char *sentinel_buf = NULL;
    size_t sentinel_cap = 0;

    // stream NULL; buffer and capacity non-NULL with sentinel values
    reset_fake(FAKE_GETLINE_SUCCESS);
    enum InputStatus s1 = read_line(NULL, &sentinel_buf, &sentinel_cap);
    bool ok = test_expect_input_status_equal(test_id,
                                             INPUT_STATUS_INVALID_ARGUMENT,
                                             s1);
    ok = ok && (sentinel_buf == NULL);
    ok = ok && (sentinel_cap == 0);
    ok = ok && (call_counter == 0);

    // buffer NULL; stream and capacity non-NULL with sentinel
    char *sentinel_buf2 = NULL;
    size_t sentinel_cap2 = 0;
    reset_fake(FAKE_GETLINE_SUCCESS);
    enum InputStatus s2 = read_line(tmpfile(), NULL, &sentinel_cap2);
    ok = test_expect_input_status_equal(test_id,
                                        INPUT_STATUS_INVALID_ARGUMENT,
                                        s2);
    ok = ok && (sentinel_buf2 == NULL);
    ok = ok && (sentinel_cap2 == 0);
    ok = ok && (call_counter == 0);

    // capacity NULL; stream and buffer non-NULL with sentinel
    FILE *tmp = tmpfile();
    char *sentinel_buf3 = NULL;
    reset_fake(FAKE_GETLINE_SUCCESS);
    enum InputStatus s3 = read_line(tmp, &sentinel_buf3, NULL);
    bool ok3 = test_expect_input_status_equal(test_id,
                                              INPUT_STATUS_INVALID_ARGUMENT,
                                              s3);
    ok = ok && ok3;
    ok = ok && (sentinel_buf3 == NULL);
    ok = ok && (call_counter == 0);
    fclose(tmp);
    return ok;
}

int main(void)
{
    struct TestCase cases[] = {
        {"LINE-01", test_line_01},
        {"LINE-02", test_line_02},
        {"LINE-03", test_line_03},
        {"LINE-04", test_line_04},
        {"LINE-05", test_line_05},
    };
    return test_run_cases(cases, sizeof(cases) / sizeof(cases[0]));
}
