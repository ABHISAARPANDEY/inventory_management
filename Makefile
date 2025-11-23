# Makefile for Inventory Management System
# Cross-platform Makefile (works on Windows with MinGW/MSYS and Unix-like systems)

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -std=c11 -g
LDFLAGS = 

# Directories
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = .

# Detect OS
ifeq ($(OS),Windows_NT)
    RM = del /Q
    RMDIR = rmdir /S /Q
    MKDIR = if not exist
    MKDIR_CMD = mkdir
    EXE_EXT = .exe
    SEP = \\
else
    RM = rm -f
    RMDIR = rm -rf
    MKDIR = mkdir -p
    MKDIR_CMD = mkdir -p
    EXE_EXT =
    SEP = /
endif

# Source files
SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Target executable
TARGET = $(BIN_DIR)/inventory$(EXE_EXT)

# Default target
all: $(TARGET)

# Create object directory if it doesn't exist
$(OBJ_DIR):
ifeq ($(OS),Windows_NT)
	@if not exist $(OBJ_DIR) mkdir $(OBJ_DIR)
else
	@$(MKDIR_CMD) $(OBJ_DIR)
endif

# Build executable
$(TARGET): $(OBJ_DIR) $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET) $(LDFLAGS)
	@echo Build complete: $(TARGET)

# Compile source files to object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Run the application
run: $(TARGET)
ifeq ($(OS),Windows_NT)
	$(TARGET)
else
	./$(TARGET)
endif

# Clean build artifacts
clean:
ifeq ($(OS),Windows_NT)
	@if exist $(OBJ_DIR) $(RMDIR) $(OBJ_DIR)
	@if exist $(TARGET) $(RM) $(TARGET)
else
	@$(RMDIR) $(OBJ_DIR)
	@$(RM) $(TARGET)
endif
	@echo Clean complete

# Install (create data directories)
install: $(TARGET)
ifeq ($(OS),Windows_NT)
	@if not exist data mkdir data
	@if not exist backup mkdir backup
else
	@$(MKDIR_CMD) data backup
endif
	@echo Installation complete

# Help target
help:
	@echo Available targets:
	@echo   make          - Build the project
	@echo   make run      - Build and run the application
	@echo   make clean    - Remove build artifacts
	@echo   make install  - Create necessary directories
	@echo   make help     - Show this help message

.PHONY: all run clean install help
