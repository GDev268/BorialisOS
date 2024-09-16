#!/usr/bin/make -f

# Compiler and flags
CC = i686-elf-g++
CFLAGS = -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti -Iinclude
LDFLAGS = -ffreestanding -nostdlib
AS = i686-elf-as
ASFLAGS = 
LD = i686-elf-gcc
LD_FLAGS = -T linker.ld -lgcc

# Directories
SRC_DIR = src
BUILD_DIR = build
ISO_DIR = $(BUILD_DIR)/isodir
GRUB_DIR = $(ISO_DIR)/boot/grub

# Source files and object files
SRCS = $(SRC_DIR)/kernel.cpp $(SRC_DIR)/gdt/gdt.cpp $(SRC_DIR)/video/vga.cpp 
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Final output
BIN = $(BUILD_DIR)/borialis.elf
ISO = $(BUILD_DIR)/borialis.iso

# Default target
all: $(BIN)

# Build target
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/boot.o: config/boot.s
	$(AS) $< -o $@

$(BIN): $(BUILD_DIR)/boot.o $(OBJS)
	$(LD) $(LD_FLAGS) -o $@ -ffreestanding -O2 -nostdlib $(BUILD_DIR)/boot.o $(OBJS)

# Join target
join: $(BIN)
	@mkdir -p $(GRUB_DIR)
	@cp $(BIN) $(ISO_DIR)/boot/borialis.bin
	@cp config/grub.cfg $(GRUB_DIR)/grub.cfg
	@grub-mkrescue -o $(ISO) $(ISO_DIR)

# Clean target
clean:
	@rm -rf $(BUILD_DIR)
	@echo "Build directory cleaned"

# Install target
install: $(ISO)
	@cd build && make install

.PHONY: all clean install join
