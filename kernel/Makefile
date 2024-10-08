
OS_NAME := "borialis"
VERSION := "0.0.1"

x86_64_c_source_files := $(wildcard src/*.c) \
$(wildcard src/**/*.c)
x86_64_c_object_files := $(patsubst src/%.c, ../build/%.o, $(x86_64_c_source_files))

x86_64_asm_source_files := $(wildcard src/*.s) \
$(wildcard src/**/*.s)
x86_64_asm_object_files := $(patsubst src/%.s, ../build/%.o, $(x86_64_asm_source_files))

x86_64_object_files := $(x86_64_c_object_files) $(x86_64_asm_object_files)

$(x86_64_c_object_files): ../build/%.o : src/%.c
	mkdir -p $(dir $@) && \
	x86_64-elf-gcc -c -I include -ffreestanding -O0 $(patsubst ../build/%.o, src/%.c, $@) -o $@

$(x86_64_asm_object_files): ../build/%.o : src/%.s
	mkdir -p $(dir $@) && \
	nasm -f elf64 $(patsubst ../build/%.o, src/%.s, $@) -o $@

.PHONY: build-x86_64
build-x86_64: $(x86_64_object_files)
	mkdir -p ../target/x86_64 && \
	x86_64-elf-ld -n -o ../target/x86_64/borialis.bin -T ../config/linker.ld $(x86_64_object_files) && \
	cp ../target/x86_64/borialis.bin ../config/isodir/boot/borialis.bin && \
	grub-mkrescue /usr/lib/grub/i386-pc -o ../target/x86_64/${OS_NAME}-${VERSION}.iso ../config/isodir
