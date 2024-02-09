/**
 * Freelist data structures track free 
 * (unallocated) blocks of memory for dynamic 
 * memory allocation. This module allows you to 
 * create and delete freelists, allocate and 
 * free memory from a freelist, get the size of 
 * a block of memory, and print the freelist.
*/
#ifndef FREELIST_H
#define FREELIST_H

#include <stdio.h>

typedef void *FreeList;

/**
 * Creates a freelist for the specified size
 * of memory and the specified range of block
 * sizes. l is the lower bound of the range,
 * and u is the upper bound of the range.
*/
extern FreeList freelistcreate(size_t size, int l, int u);

/**
 * Deletes the specified freelist and frees the
 * memory that was allocated for it.
*/
extern void     freelistdelete(FreeList f, int l, int u);

/**
 * Allocates a block of memory from the specified
 * freelist. The base parameter is the base
 * address of the memory, and e is the exponent
 * of the block size 2^e. Returns a pointer to
 * the allocated block of memory, or NULL if
 * there is no free block of the specified size.
*/
extern void *freelistalloc(FreeList f, void *base, int e, int l);

/**
 * Frees the specified block of memory from the
 * specified freelist. The base parameter is the
 * base address of the memory, and e is the
 * exponent of the block size 2^e.
*/
extern void  freelistfree(FreeList f, void *base, void *mem, int e, int l);

/**
 * Determines the size of the specified block of
 * memory in the specified freelist. The base
 * parameter is the base address of the memory,
*/
extern int freelistsize(FreeList f, void *base, void *mem, int l, int u);

/**
 * Prints the specified freelist to the standard
 * output in hexadecimal format.
*/
extern void freelistprint(FreeList f, int l, int u);

#endif
