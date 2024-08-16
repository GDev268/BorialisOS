#ifndef BORIS_GDT
#define BORIS_GDT

#define GDT_ENTRIES 8

#include <gdt/tss.h>

struct GDTEntry {
    uint16_t    limit0;
    uint16_t    base0;
    uint8_t     base1;
    uint8_t     access;
    uint8_t     limit2;
    uint8_t     base2;
} __attribute__((packed));

struct GDTDescriptor {
    uint16_t limit;
    uint64_t offset;
} __attribute__((packed));

class GDTR {
public:
    void create_descriptor(uint8_t gate, uint64_t base, uint32_t limit, uint8_t access, uint8_t granularity);
    void flush();

    uint16_t limit;
    GDTEntry offset[GDT_ENTRIES];
}

static TSS tss;

extern "C" __gdt_flush(uint64_t gdt);
extern "C" __tss_flush(uint64_t tss);

void initialize_gdt();

#endif