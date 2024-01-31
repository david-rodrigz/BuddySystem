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
 * Creates a bitmap of size bits.
*/
extern BM   bmcreate(size_t bits);
extern void bmdelete(BM b);

extern void bmset(BM b, size_t i);
extern void bmclr(BM b, size_t i);
extern int  bmtst(BM b, size_t i);

extern void bmprt(BM b);

#endif
