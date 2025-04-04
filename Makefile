# Compiler and Flags
CC = gcc
CFLAGS = -g -Wall -Wextra -pthread
LDFLAGS = -pthread

# Directories
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Source Files
SOURCES = \
	$(SRC_DIR)/cache.c \
	$(SRC_DIR)/network.c \
	$(SRC_DIR)/request_handler.c \
	$(SRC_DIR)/handler.c \
	$(SRC_DIR)/proxy_server.c \
	$(SRC_DIR)/proxy_parse.c

# Object Files
OBJECTS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SOURCES))

# Header Files
HEADERS = \
	$(SRC_DIR)/common.h \
	$(SRC_DIR)/cache.h \
	$(SRC_DIR)/network.h \
	$(SRC_DIR)/request_handler.h \
	$(SRC_DIR)/handler.h \
	$(SRC_DIR)/proxy_parse.h

# Executable
TARGET = $(BIN_DIR)/proxy

# Default Target
all: directories $(TARGET)

# Create directories
directories:
	@mkdir -p $(OBJ_DIR) $(BIN_DIR)

# Link object files
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

# Compile source files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Create tar
tar:
	tar -cvzf proxy_server.tar.gz $(SRC_DIR)/*.c $(SRC_DIR)/*.h README Makefile

.PHONY: all clean directories tar