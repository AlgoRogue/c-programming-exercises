# Derleyici ve Standartlar
CC = gcc
CFLAGS = -std=c17 -D_POSIX_C_SOURCE=200809L -Wall -Wextra -Werror -I./include
LDFLAGS = -lm

# Hedefler ve Dosyalar
BUILD_DIR = ../../../build/tests/1_basics/01_calculator
TEST_TARGET = $(BUILD_DIR)/test_calc
TEST_SRCS = tests/test_calculator.c src/calculator.c
INPUT_TEST_TARGET = $(BUILD_DIR)/test_input
INPUT_TEST_SRCS = tests/test_input.c src/input.c
INPUT_READ_TEST_TARGET = $(BUILD_DIR)/test_input_read
INPUT_READ_TEST_SRCS = tests/test_input_read.c src/input.c

# Varsayılan Hedef
all: test

test-calculator:
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(TEST_SRCS) -o $(TEST_TARGET) $(LDFLAGS)
	@echo "--- Testler Çalıştırılıyor ---"
	$(TEST_TARGET)

test-input:
	$(CC) $(CFLAGS) $(INPUT_TEST_SRCS) -o $(INPUT_TEST_TARGET) $(LDFLAGS)
	@echo "--- Input Testleri Çalıştırılıyor ---"
	$(INPUT_TEST_TARGET)

test-input-read: $(INPUT_READ_TEST_SRCS)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -Dgetline=test_getline $(INPUT_READ_TEST_SRCS) \
	    -o $(INPUT_READ_TEST_TARGET) $(LDFLAGS)
	$(INPUT_READ_TEST_TARGET)

# Birim Testlerini Derle ve Çalıştır
test: test-calculator test-input test-input-read

# Temizlik
clean:
	rm -f $(TEST_TARGET) $(INPUT_TEST_TARGET) $(INPUT_READ_TEST_TARGET)
	rm -f *.o src/*.o tests/*.o

.PHONY: all test test-calculator test-input test-input-read clean
