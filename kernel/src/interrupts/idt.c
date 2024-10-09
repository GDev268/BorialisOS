#include "interrupts/idt.h"

extern void idt_exception_handle() {
    asm volatile("cli; hlt"); //Hangs the computer
}

void idt_set_descriptor(uint8_t vector, void* isr, uint8_t flags) {
    struct idt_entry* descriptor = &idt[vector];

    descriptor->isr_low        = (uint64_t)isr & 0xFFFF;
    descriptor->kernel_cs      = 0x08;  //Kernel Code selector offset
    descriptor->ist            = 0;
    descriptor->attributes     = flags;
    descriptor->isr_mid        = ((uint64_t)isr >> 16) & 0xFFFF;
    descriptor->isr_high       = ((uint64_t)isr >> 32) & 0xFFFFFFFF;
    descriptor->reserved       = 0;
}

void idt_init(void) {
    idtr.base = (uintptr_t)&idt[0];
    idtr.limit = (uint16_t)sizeof(struct idt_entry) * IDT_MAX_DESCRIPTORS - 1;

    for(uint8_t vector = 0; vector < 32;vector++) {
            idt_set_descriptor(vector,isr_stub_table[vector],0x8E);
            vectors[vector] = true;
    }
}