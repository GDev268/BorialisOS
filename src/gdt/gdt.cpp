#include <gdt/gdt.h>
#include "gdt.h"
#include <memory>

//Explanation of each field in the Global Descriptor Table (GDT):
//  Gate: Number of the gate in the table
//  Base: Base value
//  Limit: Limit value
//  Access: Access Flag value
//  Granuality: Descriptor Flag value
void GDTR::create_descriptor(uint8_t gate, uint64_t base, uint32_t limit, uint8_t access, uint8_t granularity)
{
    offset[gate].base0 = (base & 0xFFFF);           //Lowest 8 bits of the base
    offset[gate].base1 = (base >> 16) & 0xFF;       //Middle 8 bits of the base
    offset[gate].base2 = (base >> 24) & 0xFF;       //Highest 8 bits of the base
    
    offset[gate].limit0 = (limit & 0xFFFF);         //Lowest 8 bits of the limit 
    offset[gate].limit1 = (limit >> 16) & 0x0F;     //Middle 8 bits of the limit
    offset[gate].limit1 |= granularity & 0xF0;      //Highest 4 bits of the granularity/flag    
    
    offset[gate].access = access;
}

void GDTR::flush()
{

}

static TSS tss;

// The granularity is always set to 0xA because the long mode bit (bit 5) is enabled for 64-bit code 
// segments, and bit 7 (granularity bit) is set to 1 for 4KB page granularity, while bit 6 (size bit) remains 
// 0, indicating 64-bit segments.
void initialize_gdt()
{
    GDTR gdtr;
    
    gdtr.limit = sizeof(GDTEntry) * GDT_ENTRIES - 1;

    memset(&tss, 0, sizeof(TSS));

    gdtr.create_descriptor(0, 0, 0, 0, 0);
    gdtr.create_descriptor(1, 0, 0, 0x9A, 0xA0);
    gdtr.create_descriptor(2, 0, 0, 0x92, 0xA0);
    gdtr.create_descriptor(3, 0, 0, 0xFA, 0xA0);
    gdtr.create_descriptor(4, 0, 0, 0xF2, 0xA0);
    gdtr.create_descriptor(5, (uint64_t)&tss, sizeof(tss), 0x89, 0x40);
    gdtr.create_descriptor(6, 0, 0, 0, 0);
    gdtr.create_descriptor(7, 0, 0, 0, 0);

    gdtr.flush();
}