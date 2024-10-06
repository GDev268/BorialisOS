#ifndef BORIS_MEMORY
#define BORIS_MEMORY

#include "types.h"

void* memset(void* dest, int c, size_t n) 
{
    if(n <= 0)
        return dest;

    size_t sz = n;
    size_t i = 0;

    for (i; i < n;)
    {
        uint64_t dest_curr = (uint64_t)dest + i;

        if((sz >= 4) && !(dest_curr & 0x3))
        {
            *(uint32_t*)dest_curr = (uint32_t)c;

            sz -= 4;
            i += 4;
        }
        else if((sz >= 2) && !(dest_curr & 0x1))
        {
            *(uint16_t*)dest_curr = (uint16_t)c;

            sz -= 2;
            i += 2;
        }
        else
        {
            *(uint8_t*)dest_curr = (uint8_t)c;

            sz -= 1;
            i += 1;
        }
    }

    //__memset(dest, c, n);
    return dest;
}

#endif