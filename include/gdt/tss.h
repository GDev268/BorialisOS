#ifndef BORIS_TSS
#define BORIS_TSS

struct TSS {
    uint32_t rsv0;      //Reserved 0
    uint64_t rsp[3];    //Stack Pointers
    uint64_t rsv1;      //Reserved 1
    uint64_t ist[7];    //Interrupt Stack Table
    uint64_t rsv2;      //Reserved 2
    uint16_t rsv3;      //Reserved 3
    uint16_t iopb_off;  //I/O Map Base Address Field
} __attribute__((packed));

#endif