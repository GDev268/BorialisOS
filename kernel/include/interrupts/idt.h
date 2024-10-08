#ifndef BORIS_IDT
#define BORIS_IDT

#include "utils/types.h"
#include <stdbool.h>

#define IDT_MAX_DESCRIPTORS 256

static bool vectors[IDT_MAX_DESCRIPTORS];

extern void* isr_stub_table[];

typedef struct __attribute__((packed)) idt_entry {
    uint16_t    isr_low;      // The lower 16 bits of the ISR's address
	uint16_t    kernel_cs;    // The GDT segment selector that the CPU will load into CS before calling the ISR
	uint8_t	    ist;          // The IST in the TSS that the CPU will load into RSP; set to zero for now
	uint8_t     attributes;   // Type and attributes; see the IDT page
	uint16_t    isr_mid;      // The higher 16 bits of the lower 32 bits of the ISR's address
	uint32_t    isr_high;     // The higher 32 bits of the ISR's address
	uint32_t    reserved;     // Set to zero  
};

__attribute__((aligned(0x10))) 
static struct idt_entry idt[256];

typedef struct __attribute__((packed)) idtr_t {
	uint16_t	limit;
	uint64_t	base;
};

static struct idtr_t idtr;

__attribute__((noreturn))
extern void idt_exception_handle(void);

void idt_set_descriptor(uint8_t vector, void* isr, uint8_t flags);

void idt_init();
#endif