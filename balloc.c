#include "balloc.h"
#include "utils.h"
#include "freelist.h"

Balloc bcreate(unsigned int size, int l, int u) {
    // Check for invalid input
    // if size < 2^l or size > 2^u, return 0
    if (size < (1 << l) || size > (1 << u)) {
        return 0;
    }

    // Calculate the size of the memory pool in bytes
    unsigned int poolSize = bits2bytes(size);

    // Calculate the number of freelists
    int numFreelists = u - l + 1;

    // Obtain memory from mmap for the memory pool and freelists
    void *p = mmalloc(sizeof(unsigned int) * 3 + sizeof(FreeList) * numFreelists + poolSize);

    // If the allocation failed, return 0
    if ((long)p == -1) {
        return 0;
    }

    // Store the metadata
    unsigned int *meta = p;
    meta[0] = size;
    meta[1] = l;
    meta[2] = u;

    // Get a pointer to the start of the freelists
    FreeList *freelists = (FreeList *)(meta + 3);

    // Initialize the freelists
    for (int i = 0; i < numFreelists; i++) {
        freelists[i] = freelistcreate(size, l + i, l + i);
        if (freelists[i] == NULL) {
            // If freelist creation failed, free all allocated memory and return 0
            for (int j = 0; j < i; j++) {
                freelistdelete(size, l + j, l + j);
            }
            mmfree(p, sizeof(unsigned int) * 3 + sizeof(FreeList) * numFreelists + poolSize);
            return 0;
        }
    }

    // Get a pointer to the start of the memory pool
    Balloc pool = (Balloc)(freelists + numFreelists);

    // Clear the memory pool
    memset(pool, 0, poolSize);
    
    return pool;
}

void bdelete(Balloc pool) {
    // Get a pointer to the metadata
    unsigned int *meta = pool;
    meta--;

    // Get the size of the memory pool
    unsigned int size = meta[0];

    // Get the range of the freelists
    int l = meta[1];
    int u = meta[2];

    // Get a pointer to the start of the freelists
    FreeList *freelists = (FreeList *)(meta + 3);

    // Delete the freelists
    for (int i = 0; i < u - l + 1; i++) {
        freelistdelete(size, l + i, l + i);
    }

    // Free the memory
    mmfree(meta, sizeof(unsigned int) * 3 + sizeof(FreeList) * (u - l + 1) + bits2bytes(size));
}

void *balloc(Balloc pool, unsigned int size) {
    // Get a pointer to the metadata
    unsigned int *meta = pool;
    meta--;

    // Get the size of the memory pool
    unsigned int poolSize = meta[0];

    // Get the range of the freelists
    int l = meta[1];
    int u = meta[2];

    // Get a pointer to the start of the freelists
    FreeList *freelists = (FreeList *)(meta + 3);

    // Find the appropriate freelist
    int e = size2e(size);
    if (e < l) {
        e = l;
    } else if (e > u) {
        e = u;
    }

    // Get a pointer to the appropriate freelist
    FreeList fl = freelists[e - l];

    // Allocate memory from the freelist
    void *mem = freelistalloc(fl, pool, e, l);

    // If the allocation failed, return NULL
    if (mem == NULL) {
        return NULL;
    }

    // Calculate the index of the allocated memory
    unsigned int index = (mem - pool) / e2size(e);

    // Set the corresponding bit in the memory pool
    bitset(pool, index);

    return mem;
}

void bfree(Balloc pool, void *mem) {
    // Get a pointer to the metadata
    unsigned int *meta = pool;
    meta--;

    // Get the size of the memory pool
    unsigned int poolSize = meta[0];

    // Get the range of the freelists
    int l = meta[1];
    int u = meta[2];

    // Get a pointer to the start of the freelists
    FreeList *freelists = (FreeList *)(meta + 3);

    // Calculate the index of the memory to be freed
    unsigned int index = (mem - pool) / e2size(size2e(bsize(pool, mem)));

    // Clear the corresponding bit in the memory pool
    bitclr(pool, index);

    // Get the size of the memory to be freed
    unsigned int size = bsize(pool, mem);

    // Get a pointer to the appropriate freelist
    FreeList fl = freelists[size2e(size) - l];

    // Free the memory in the freelist
    freelistfree(fl, pool, mem, size2e(size), l);
}

unsigned int bsize(Balloc pool, void *mem) {
    // Get a pointer to the metadata
    unsigned int *meta = pool;
    meta--;

    // Get the size of the memory pool
    unsigned int poolSize = meta[0];

    // Get the range of the freelists
    int l = meta[1];
    int u = meta[2];

    // Get a pointer to the start of the freelists
    FreeList *freelists = (FreeList *)(meta + 3);

    // Calculate the index of the memory
    unsigned int index = (mem - pool) / e2size(size2e(bsize(pool, mem)));

    // Get the corresponding bit in the memory pool
    int bit = bittst(pool, index);

    // If the bit is not set, return 0
    if (!bit) {
        return 0;
    }

    // Get the size of the memory
    unsigned int size = e2size(size2e(bsize(pool, mem)));

    return size;
}

void bprint(Balloc pool) {
    // Get a pointer to the metadata
    unsigned int *meta = pool;
    meta--;

    // Get the size of the memory pool
    unsigned int poolSize = meta[0];

    // Get the range of the freelists
    int l = meta[1];
    int u = meta[2];

    // Get a pointer to the start of the freelists
    FreeList *freelists = (FreeList *)(meta + 3);

    // Print the memory pool
    bmprt(pool);

    // Print the freelists
    for (int i = 0; i < u - l + 1; i++) {
        freelistprint(freelists[i], l + i, l + i);
    }
}