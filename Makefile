SRC_DIR	  := src
INC_DIR   := include
BUILD_DIR := build

TARGET := $(BUILD_DIR)/json-parser-c

SRC := $(wildcard $(SRC_DIR)/*.c)
INC := $(addprefix -I, $(INC_DIR))
OBJ := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC))

CC := gcc
CFLAGS := -std=gnu11 -Wall -Wextra -O2

all: $(TARGET)

debug: CFLAGS += -g
debug: all

.PHONY: debug all clean

$(BUILD_DIR):
	@mkdir -p $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	@$(CC) $(CFLAGS) -c $< $(INC) -o $@ 

$(TARGET): $(OBJ)
	@$(CC) $^ -o $@ -lbsd
	@echo "-> $@"

clean:
	rm -rf $(BUILD_DIR)
