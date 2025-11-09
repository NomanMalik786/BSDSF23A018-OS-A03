CC = gcc
CFLAGS = -Iinclude -Wall -g
LDFLAGS = -lreadline

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

TARGET = $(BIN_DIR)/myshell
OBJS = $(OBJ_DIR)/main.o $(OBJ_DIR)/shell.o $(OBJ_DIR)/history.o

$(OBJ_DIR) $(BIN_DIR):
	mkdir -p $(OBJ_DIR) $(BIN_DIR)

all: $(OBJ_DIR) $(BIN_DIR) $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c include/shell.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

run: all
	./$(TARGET)

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
