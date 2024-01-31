#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>

static const int bitsperbyte=8;

/**
 * Uses mmap to allocate a block of memory of 
 * the specified size that is private to this 
 * process and can be both read from and 
 * written to. Returns a pointer to the
 * allocated memory block, or -1 if the
 * allocation failed.
*/
extern void *mmalloc(size_t size);

/**
 * Uses munmap to free the block of memory at 
 * the specified address and of the specified 
 * size.
*/
extern void mmfree(void *p, size_t size);

/**
 * Divides the first number by the second 
 * number and rounds up to the nearest whole 
 * number. Returns the result.
*/
extern size_t divup(size_t n, size_t d);

/**
 * Converts the specified number of bits to 
 * bytes.
*/
extern size_t bits2bytes(size_t bits);

/**
 * Returns 2 to the power of e.
*/
extern size_t e2size(int e);

/**
 * Returns the smallest power of 2 that is 
 * greater than or equal to the specified 
 * number.
*/
extern int size2e(size_t size);

/**
 * Sets the specified bit in the specified
 * memory block to 1.
*/
extern void bitset(void *p, int bit);

/**
 * Sets the specified bit in the specified
 * memory block to 0.
*/
extern void bitclr(void *p, int bit);

/**
 * Inverts the specified bit in the specified
 * memory block.
*/
extern void bitinv(void *p, int bit);

/**
 * Returns the value of the specified bit in 
 * the specified memory block.
*/
extern int  bittst(void *p, int bit);

#endif
