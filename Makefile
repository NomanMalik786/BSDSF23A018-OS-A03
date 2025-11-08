# Makefile for Base Shell (PA-03)

# Compiler
CC = gcc

# Directories
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj
BIN_DIR = bin

# Target
TARGET = $(BIN_DIR)/myshell

# Compiler flags
CFLAGS = -I$(INC_DIR) -Wall -g

# Source files and object files
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

# Default rule
all: $(BIN_DIR) $(OBJ_DIR) $(TARGET)

# Link object files to create the final executable
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@

# Compile .c files into .o files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Create directories if not present
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Clean build artifacts
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Run the shell
run: all
	./$(TARGET)
