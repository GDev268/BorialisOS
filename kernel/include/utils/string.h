#ifndef BORIS_STRING
#define BORIS_STRING

#include "utils/types.h"

size_t strlen(const char* str) {
    size_t len = 0;

    while (str[len])
    {
        len++;
    }
    
    return len;
}

#endif