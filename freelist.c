#include "freelist.h"
#include "bm.h"
#include "utils.h"

extern FreeList freelistcreate(size_t size, int l, int u) {
    // Calculate the number of bytes needed for the freelist
    size_t bytes = bits2bytes(size);

    // Allocate memory for the metadata and the freelist
    size_t *p = mmalloc(sizeof(size_t) * 3 + bytes);
    if ((long)p == -1) {
        return NULL; // Allocation failed
    }

    // Store the metadata
    p[0] = size;
    p[1] = l;
    p[2] = u;

    // Get a pointer to the start of the freelist
    FreeList fl = p + 3;

    // Initialize the freelist to 0
    memset(fl, 0, bytes);

    return fl;
}

extern void freelistdelete(FreeList f, int l, int u) {
    // Free the memory used by the freelist
    size_t *p = f;
    p -= 3;
    mmfree(p, bits2bytes(p[0]));
}

extern void *freelistalloc(FreeList f, void *base, int e, int l) {
    // Get the size of the memory block
    size_t size = e2size(e);

    // Find the first free block of the appropriate size
    size_t offset = 0;
    for (size_t i = 0; i < bmbits(f); i++) {
        if (!bmtst(f, i)) {
            size_t j = i;
            while (j < bmbits(f) && !bmtst(f, j)) {
                j++;
            }
            if (j - i >= size) {
                offset = i;
                break;
            }
            i = j;
        }
    }

    // If no free block was found, return NULL
    if (offset == 0) {
        return NULL;
    }

    // Mark the block as allocated
    for (size_t i = 0; i < size; i++) {
        bmset(f, offset + i);
    }

    // Return a pointer to the allocated memory
    return (char *)base + offset;
}

extern void  freelistfree(FreeList f, void *base, void *mem, int e, int l) {
    // Get the size of the memory block
    size_t size = e2size(e);

    // Get the offset of the memory block from the base
    size_t offset = (char *)mem - (char *)base;

    // Mark the block as free
    for (size_t i = 0; i < size; i++) {
        bmclr(f, offset + i);
    }
}

extern int freelistsize(FreeList f, void *base, void *mem, int l, int u) {
    // Get the offset of the memory block from the base
    size_t offset = (char *)mem - (char *)base;

    // Get the size of the memory block
    size_t size = 1 << l;

    // Find the size of the memory block
    while (size < offset) {
        size <<= 1;
        l++;
    }

    return l;
}

extern void freelistprint(FreeList f, int l, int u) {
    // Print the freelist
    bmprt(f);
}
