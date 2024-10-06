x86_64_c_source_files := $(wildcard src/*.cpp) \
$(wildcard src/**/*.cpp)
x86_64_c_object_files := $(patsubst src/%.cpp, ../build/%.o, $(x86_64_c_source_files))

x86_64_asm_source_files := $(wildcard src/*.s) \
$(wildcard src/**/*.s)
x86_64_asm_object_files := $(patsubst src/%.s, ../build/%.o, $(x86_64_asm_source_files))

x86_64_object_files := $(x86_64_c_object_files) $(x86_64_asm_object_files)

$(x86_64_c_object_files): ../build/%.o : src/%.cpp
	mkdir -p $(dir $@) && \
	x86_64-elf-g++ -c -I include -ffreestanding -O0 $(patsubst ../build/%.o, src/%.cpp, $@) -o $@

$(x86_64_asm_object_files): ../build/%.o : src/%.s
	mkdir -p $(dir $@) && \
	nasm -f elf64 $(patsubst ../build/%.o, src/%.s, $@) -o $@

.PHONY: build-x86_64
build-x86_64: $(x86_64_object_files)
	mkdir -p dist/x86_64 && \
	x86_64-elf-ld -n -o ../dist/x86_64/kernel.bin -T ../config/linker.ld $(x86_64_object_files) && \
	cp ../dist/x86_64/kernel.bin ../config/isodir/boot/kernel.bin && \
	grub-mkrescue /usr/lib/grub/i386-pc -o ../dist/x86_64/kernel2.iso ../config/isodir
