#ifndef BALLOC_H
#define BALLOC_H

typedef void *Balloc;

/**
 * Creates a memory allocator given the total 
 * number of bytes that can be allocated 
 * (size), The l (lower) argument specifies 
 * that the smallest allocation will be 2^l 
 * bytes, even if a smaller amount is 
 * requested. The u (upper) argument specifies 
 * that the largest allocation will be 2^u 
 * bytes; a larger request will fail.
*/
extern Balloc bcreate(unsigned int size, int l, int u);
extern void   bdelete(Balloc pool);

extern void *balloc(Balloc pool, unsigned int size);
extern void  bfree(Balloc pool, void *mem);

extern unsigned int bsize(Balloc pool, void *mem);
extern void bprint(Balloc pool);

#endif
