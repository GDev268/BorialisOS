#!/usr/bin/make -f

# Default target
all: build

# Build target

# @cmake --preset build && cd build && make && MyExecutable.exe
build:
	i686-elf-as config/boot.s -o build/boot.o
	i686-elf-g++ -c src/kernel.cpp -o build/kernel.o -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti
	i686-elf-gcc -T linker.ld -o build/borialis.bin -ffreestanding -O2 -nostdlib build/boot.o build/kernel.o -lgcc

join:
	@mkdir -p build/isodir/boot/grub
	@cp build/borialis.bin build/isodir/boot/borialis.bin
	@cp config/grub.cfg build/isodir/boot/grub/grub.cfg
	@grub-mkrescue -o build/borialis.iso build/isodir

# Clean target
clean:
	@rmdir build
	@echo "Build directory cleaned"

# Install target
install: build
	@cd build && make install

.PHONY: all build clean install