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

APP_TARGET = ../../../build/solutions/1_basics/01_calculator/calc
APP_SRCS = src/main.c src/calculator.c src/input.c
FAULT_MAIN_OBJ = $(BUILD_DIR)/main_fault.o
FAULT_INPUT_OBJ = $(BUILD_DIR)/input_fault.o
FAULT_TARGET = $(BUILD_DIR)/calc_fault

calc: $(APP_TARGET)

test-cli: $(APP_TARGET)
	sh tests/test_cli.sh "$(APP_TARGET)"

$(APP_TARGET): $(APP_SRCS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(APP_SRCS) -o $(APP_TARGET) $(LDFLAGS)

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
test: test-calculator test-input test-input-read test-cli test-resources


$(FAULT_MAIN_OBJ): src/main.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -Dfree=test_free -c src/main.c -o $(FAULT_MAIN_OBJ)

$(FAULT_INPUT_OBJ): src/input.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -Dgetline=test_getline -c src/input.c -o $(FAULT_INPUT_OBJ)

$(FAULT_TARGET): $(FAULT_MAIN_OBJ) $(FAULT_INPUT_OBJ) src/calculator.c tests/fake_runtime.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(FAULT_MAIN_OBJ) $(FAULT_INPUT_OBJ) src/calculator.c tests/fake_runtime.c -o $(FAULT_TARGET) $(LDFLAGS)

# Temizlik
clean:
	rm -f $(TEST_TARGET) $(INPUT_TEST_TARGET) $(INPUT_READ_TEST_TARGET) $(APP_TARGET) $(FAULT_TARGET) $(FAULT_MAIN_OBJ) $(FAULT_INPUT_OBJ)
	rm -f *.o src/*.o tests/*.o

.PHONY: all test test-calculator test-input test-input-read test-cli test-resources calc clean


test-resources: $(FAULT_TARGET)
	sh tests/test_resources.sh "$(FAULT_TARGET)"
