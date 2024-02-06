// A general-purpose bitmap.
/**
 * A bitmap is a data structure that is used to 
 * manage memory. It is essentially an array of 
 * bits, where each bit represents a block of 
 * memory. If a bit is set (1), it means that 
 * the corresponding block of memory is in use. 
 * If a bit is clear (0), it means that the 
 * corresponding block of memory is free.
*/
#ifndef BM_H
#define BM_H

#include <stdio.h>

typedef void *BM;

/**
 * Creates a bitmap with the specified number 
 * of bits and initializes all bits to 0. The 
 * number of bits is stored at the beginning of 
 * the allocated memory.
*/
extern BM   bmcreate(size_t bits);

/**
 * Deletes the specified bitmap and frees the
 * memory that was allocated for it.
*/
extern void bmdelete(BM b);

/**
 * Sets the specified bit in the bitmap. The 
 * bit index must be less than the number of 
 * bits in the bitmap.
*/
extern void bmset(BM b, size_t i);

/**
 * Clears the specified bit in the bitmap. The
 * bit index must be less than the number of
 * bits in the bitmap.
*/
extern void bmclr(BM b, size_t i);

/**
 * Tests the specified bit in the bitmap. The
 * bit index must be less than the number of
 * bits in the bitmap.
*/
extern int  bmtst(BM b, size_t i);

/**
 * Prints the specified bitmap to the standard
 * output in hexadecimal format.
*/
extern void bmprt(BM b);

#endif
