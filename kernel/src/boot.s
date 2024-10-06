global start
extern long_mode_start
extern kernel_main
extern setup_kernel

section .text
bits 32
start:
	mov esp, stack_top

	;Doesn't Work on C++ Enviroment so needs to be declared seperatly
	call check_multiboot

	call setup_kernel

	;call check_cpuid
	;call check_long_mode

	;call setup_page_tables
	;call enable_paging

	;call gdt_init
	
	lgdt [GDT.Pointer]
	jmp 0x8:long_mode_start
	;call kernel_main

	hlt

global check_multiboot
global check_cpuid
global check_long_mode
global setup_page_tables
global enable_paging

check_multiboot:
	cmp eax, 0x36d76289
	jne .no_multiboot
	ret
.no_multiboot:
	mov al, "M"
	jmp error

check_cpuid:
	pushfd
	pop eax
	mov ecx, eax
	xor eax, 1 << 21
	push eax
	popfd
	pushfd
	pop eax
	push ecx
	popfd
	cmp eax, ecx
	je .no_cpuid
	ret
.no_cpuid:
	mov al, "C"
	jmp error

check_long_mode:
	mov eax, 0x80000000
	cpuid
	cmp eax, 0x80000001
	jb .no_long_mode

	mov eax, 0x80000001
	cpuid
	test edx, 1 << 29
	jz .no_long_mode
	
	ret
.no_long_mode:
	mov al, "L"
	jmp error

setup_page_tables:
	mov eax, page_table_l3
	or eax, 0b11 ; present, writable
	mov [page_table_l4], eax
	
	mov eax, page_table_l2
	or eax, 0b11 ; present, writable
	mov [page_table_l3], eax

	mov ecx, 0 ; counter
.loop:

	mov eax, 0x200000 ; 2MiB
	mul ecx
	or eax, 0b10000011 ; present, writable, huge page
	mov [page_table_l2 + ecx * 8], eax

	inc ecx ; increment counter
	cmp ecx, 512 ; checks if the whole table is mapped
	jne .loop ; if not, continue

	ret

enable_paging:
	; pass page table location to cpu
	mov eax, page_table_l4
	mov cr3, eax

	; enable PAE
	mov eax, cr4
	or eax, 1 << 5
	mov cr4, eax

	; enable long mode
	mov ecx, 0xC0000080
	rdmsr
	or eax, 1 << 8
	wrmsr

	; enable paging
	mov eax, cr0
	or eax, 1 << 31
	mov cr0, eax

	ret

error:
	; print "ERR: X" where X is the error code
	mov dword [0xb8000], 0x4f524f45
	mov dword [0xb8004], 0x4f3a4f52
	mov dword [0xb8008], 0x4f204f20
	mov byte  [0xb800a], al
	hlt


;Need to initialize GDT on assembly mode
%macro GDTE 4
  dw %2 & 0xFFFF
  dw %1
  db %1 >> 16
  db %3
  db (%2 >> 16) & 0x0F | (%4 << 4)
  db %1 >> 24
%endmacro

%define offset(addr) ( 0x100000 + addr - $$ )
%macro GDT64 4
  dw %2 & 0xFFFF
  dw %1 & 0xFFFF
  db (%1 >> 16) & 0xFF
  db %3
  db (%2 >> 16) & 0x0F | (%4 << 4)
  db (%1 >> 24) & 0xFF
  dd (%1 >> 32)
  dd 0
%endmacro

GDT:
	; Null segment
    GDTE 0, 0, 0, 0 ; Gate 0

    ; Kernel code segment (0x9A = present, ring 0, executable, read)
    GDTE 0, 0xfffff, 10011010b, 1010b ; Gate 1 (Kernel code segment)

    ; Kernel data segment (0x92 = present, ring 0, writable, non-executable)
    GDTE 0, 0xfffff, 10010010b, 1010b ; Gate 2 (Kernel data segment)

    ; User mode code segment (0xFA = present, ring 3, executable, read)
    GDTE 0, 0xfffff, 11111010b, 1010b ; Gate 3 (User code segment)

    ; User mode data segment (0xF2 = present, ring 3, writable, non-executable)
    GDTE 0, 0xfffff, 11110010b, 1010b ; Gate 4 (User data segment)

    ; TSS segment
	GDT64 0xFFFFFFFFC0000000 + offset(tss64), (end_tss64 - tss64), 11101001b, 0001b

ALIGN 4
    dw 0
.Pointer:
    dw $ - GDT - 1
    .p:
    dd GDT
    dd 0
    
align 8
tss64:
  dd 0
global k_tss64_sp
k_tss64_sp:
  dq 0 ; rsp will be set to this value when switching back to kernel
  TIMES 23 dd 0
end_tss64:



section .bss
align 4096
page_table_l4:
	resb 4096
page_table_l3:
	resb 4096
page_table_l2:
	resb 4096
stack_bottom:
	resb 4096 * 4
stack_top:
