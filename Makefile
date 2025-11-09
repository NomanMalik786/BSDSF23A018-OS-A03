# Compiler and flags
CC = gcc
CFLAGS = -Iinclude -Wall -g

# Directories
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Target
TARGET = $(BIN_DIR)/myshell

# Source and object files
OBJS = $(OBJ_DIR)/main.o $(OBJ_DIR)/shell.o $(OBJ_DIR)/execute.o $(OBJ_DIR)/history.o

# Ensure directories exist (order-only prerequisites)
$(OBJ_DIR) $(BIN_DIR):
	mkdir -p $(OBJ_DIR) $(BIN_DIR)

# Default rule
all: $(OBJ_DIR) $(BIN_DIR) $(TARGET)

# Link
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

# Generic rule to compile .c -> .o (depends on OBJ_DIR)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c include/shell.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Run the shell
run: all
	./$(TARGET)

# Clean
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

