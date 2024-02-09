// A baddr bitmap, for the Buddy System.
/**
 * This is a block address (baddr) bitmap that is used 
 * to manage memory in the Buddy System.
*/
#ifndef BBM_H
#define BBM_H

#include <stdio.h>

typedef void *BBM;

/**
 * Creates a baddr bitmap of size bytes, given 
 * the size of memory and the exponent e of the 
 * smallest block size 2^e. Returns a pointer to
 * the bitmap.
*/
extern BBM  bbmcreate(size_t size, int e);
extern void bbmdelete(BBM b);

extern void bbmset(BBM b, void *base, void *mem, int e);
extern void bbmclr(BBM b, void *base, void *mem, int e);
extern  int bbmtst(BBM b, void *base, void *mem, int e);

extern void bbmprt(BBM b);

extern void *baddrset(void *base, void *mem, int e);
extern void *baddrclr(void *base, void *mem, int e);
extern void *baddrinv(void *base, void *mem, int e);
extern int   baddrtst(void *base, void *mem, int e);

#endif
