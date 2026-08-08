# Derleyici ve Standartlar
CC = gcc
CFLAGS = -std=c17 -D_POSIX_C_SOURCE=200809L -Wall -Wextra -Werror -I./include
LDFLAGS = -lm

# Hedefler ve Dosyalar
BUILD_DIR = ../../../build/tests/1_basics/01_calculator
TEST_TARGET = $(BUILD_DIR)/test_calc
TEST_SRCS = tests/test_calculator.c src/calculator.c

# Varsayılan Hedef
all: test

# Birim Testlerini Derle ve Çalıştır
test: $(TEST_SRCS)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(TEST_SRCS) -o $(TEST_TARGET) $(LDFLAGS)
	@echo "--- Testler Çalıştırılıyor ---"
	$(TEST_TARGET)

# Temizlik
clean:
	rm -f test_calc $(TEST_TARGET)
	rm -f *.o src/*.o tests/*.o

.PHONY: all test clean
