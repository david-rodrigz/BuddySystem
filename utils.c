#include <sys/mman.h>
#include <stdio.h>
#include <math.h>

#include "utils.h"

extern void* mmalloc(size_t size) {
    void* addr = mmap(0, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (addr == MAP_FAILED) {
        return -1;
    }
    return addr;
}

extern void mmfree(void* addr, size_t size) {
    munmap(addr, size);
}

extern size_t divup(size_t n, size_t d) {
    // divide n by d 
    double result = (double)n / (double)d;
    // round up to the nearest whole number
    return round(result);
}

extern size_t bits2bytes(size_t bits) {
    return divup(bits, 8);
}

extern size_t e2size(int e) {
    return 1 << e;
}

extern int size2e(size_t size) {
    int e = 0;
    while (size > 1) {
        size = size >> 1;
        e++;
    }
    return e;
}

extern void bitset(void* p, int bit) {
    // get the byte that contains the bit
    char* byte = (char*)p + bit / 8;
    // set the bit (OR with 1 and shift left by the remainder of bit / 8)
    *byte |= 1 << (bit % 8);
}

extern void bitclr(void* p, int bit) {
    // get the byte that contains the bit
    char* byte = (char*)p + bit / 8;
    // clear the bit (AND with the complement of 1 and shift left by the remainder of bit / 8)
    *byte &= ~(1 << (bit % 8));
}

extern void bitinv(void *p, int bit) {
    // get the byte that contains the bit
    char* byte = (char*)p + bit / 8;
    // invert the bit (XOR with 1 and shift left by the remainder of bit / 8)
    *byte ^= 1 << (bit % 8);
}

extern int bittst(void* p, int bit) {
    // get the byte that contains the bit
    char* byte = (char*)p + bit / 8;
    // return the value of the bit
    return (*byte >> (bit % 8)) & 1;
}