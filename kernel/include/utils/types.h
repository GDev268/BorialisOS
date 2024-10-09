#ifndef BORIS_TYPES
#define BORIS_TYPES

typedef signed char int8_t;
typedef short int int16_t;
typedef int int32_t;
typedef long long int int64_t;

typedef unsigned char uint8_t;
typedef unsigned short int uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long int uint64_t;

typedef uint64_t size_t;

#if defined(__x86_64__) || defined(_M_X64)  // 64-bit architecture
typedef uint64_t uintptr_t;
#elif defined(__i386__) || defined(_M_IX86) // 32-bit architecture
typedef uint32_t uintptr_t;
#else
#error "Unsupported architecture"
#endif

#endif