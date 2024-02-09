#include <stdlib.h>
#include <string.h>

#include "bm.h"
#include "utils.h"

static size_t bmbits(BM b) { size_t *bits=b; return *--bits; }

static size_t bmbytes(BM b) { return bits2bytes(bmbits(b)); }

static void ok(BM b, size_t i) {
  if (i<bmbits(b))
    return;
  fprintf(stderr,"bitmap index out of range\n");
  exit(1);
}

extern BM bmcreate(size_t bits) {
  // get the number of bytes needed to store the bits
  size_t bytes=bits2bytes(bits);

  // map a block of memory of size bytes and store the number of bits at the beginning
  // p is a pointer to the beginning of the memory block
  size_t *p=mmalloc(sizeof(size_t)+bytes);
  if ((long)p==-1)
    return 0;
  
  // store the number of bits at the beginning of the memory block
  *p=bits;

  // increment p to point to the beginning of the bitmap
  // b is a pointer to the beginning of the memory block
  BM b=++p;

  // set all bytes to 0 (clear the bitmap)
  memset(b,0,bytes);
  
  return b;
}

extern void bmdelete(BM b) {
  size_t *p=b;
  p--;
  mmfree(p,*p);
}

extern void bmset(BM b, size_t i) {
  ok(b,i); bitset(b+i/bitsperbyte,i%bitsperbyte);
}

extern void bmclr(BM b, size_t i) {
  ok(b,i); bitclr(b+i/bitsperbyte,i%bitsperbyte);
}

extern int bmtst(BM b, size_t i) {
  ok(b,i); return bittst(b+i/bitsperbyte,i%bitsperbyte);
}

extern void bmprt(BM b) {
  for (int byte=bmbytes(b)-1; byte>=0; byte--)
    printf("%02x%s",((char *)b)[byte],(byte ? " " : "\n"));
}
