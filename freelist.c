#include <string.h>
#include <stdlib.h>
#include "freelist.h"
#include "bm.h"
#include "utils.h"

// Define a structure for the free block
typedef struct FreeBlock {
    struct FreeBlock *next; // Pointer to the next free block of the same size
} FreeBlock;

// Define a structure to manage free blocks at different sizes
typedef struct FreeListStruct {
    int size; // Size of blocks managed by this free list
    FreeBlock *head; // Pointer to the head of the free blocks of this size
} FreeListStruct;

extern FreeList freelistcreate(size_t size, int l, int u) {
    FreeListStruct* free_lists = malloc((u - l + 1) * sizeof(FreeList));

    // Initialize each free list for different block sizes
    for (int i = l; i <= u; ++i) {
        free_lists[i - l].size = 1 << i; // Calculate block size
        free_lists[i - l].head = NULL; // Initialize head pointer to NULL
        // Other initialization if needed
    }

    return free_lists;
}

extern void freelistdelete(FreeList f, int l, int u) {
    struct FreeListStruct *fl = (struct FreeListStruct *)f;
    
    // Free the memory allocated for the free lists
    free(fl);
}

extern void *freelistalloc(FreeList f, void *base, int e, int l) {
    struct FreeListStruct *fl = (struct FreeListStruct *)f;
    
    // Find the smallest block size that can accommodate the requested size
    while (l <= e) {
        if (fl[l].head != NULL) {
            // If there is a free block of the required size, allocate it
            FreeBlock *block = fl[l].head;
            fl[l].head = block->next;
            return block;
        }
        l++;
    }
    return NULL;
}

extern void  freelistfree(FreeList f, void *base, void *mem, int e, int l) {
    struct FreeListStruct *fl = (struct FreeListStruct *)f;
    
    // Get the offset of the memory block from the base
    size_t offset = (char *)mem - (char *)base;

    // Get the size of the memory block
    size_t size = 1 << l;

    // Find the size of the memory block
    while (size < offset) {
        size <<= 1;
        l++;
    }

    // Create a new free block and add it to the free list
    FreeBlock *block = (FreeBlock *)mem;
    block->next = fl[l].head;
    fl[l].head = block;
}

extern int freelistsize(FreeList f, void *base, void *mem, int l, int u) {
    struct FreeListStruct *fl = (struct FreeListStruct *)f;
    
    // Get the offset of the memory block from the base
    size_t offset = (char *)mem - (char *)base;

    // Get the size of the memory block
    size_t size = 1 << l;

    // Find the size of the memory block
    while (size < offset) {
        size <<= 1;
        l++;
    }

    // Return the size of the memory block
    return size;
}

extern void freelistprint(FreeList f, int l, int u) {
    struct FreeListStruct *fl = (struct FreeListStruct *)f;
    
    // Print the free blocks in each free list
    for (int i = l; i <= u; ++i) {
        printf("Free list for block size %d:\n", 1 << i);
        FreeBlock *block = fl[i].head;
        while (block != NULL) {
            printf("%p -> ", block);
            block = block->next;
        }
        printf("NULL\n");
    }
}
