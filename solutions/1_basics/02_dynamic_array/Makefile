# Derleyici ve Standartlar
CC = gcc
CFLAGS = -std=c17 -D_POSIX_C_SOURCE=200809L -Wall -Wextra -Werror -I./include
LDFLAGS =

# Hedefler ve Dosyalar
BUILD_DIR = ../../../build/tests/1_basics/02_dynamic_array
TEST_TARGET = $(BUILD_DIR)/test_dynamic_array
TEST_SRCS = tests/test_dynamic_array.c src/dynamic_array.c

DYNAMIC_ARRAY_HEADERS = include/dynamic_array.h
TEST_HEADERS = tests/test_helpers.h

# Varsayılan Hedef
all: test

test-dynamic-array: $(TEST_SRCS) $(DYNAMIC_ARRAY_HEADERS) $(TEST_HEADERS)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(TEST_SRCS) -o $(TEST_TARGET) $(LDFLAGS)
	@echo "--- Testler Çalıştırılıyor ---"
	$(TEST_TARGET)

# Birim Testlerini Derle ve Çalıştır
test: test-dynamic-array

# Temizlik
clean:
	rm -f $(TEST_TARGET)
	rm -f *.o src/*.o tests/*.o

.PHONY: all test test-dynamic-array clean
