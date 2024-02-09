#include <stdio.h>
#include <assert.h>
#include "freelist.h"
#include "balloc.h"

// Test case 1: Basic allocation and deallocation
void test_basic_allocation() {
    Balloc allocator = bcreate(1024, 0, 10);
    void *mem1 = balloc(allocator, 64);
    assert(mem1 != NULL && "Failed to allocate memory");
    bfree(allocator, mem1);
    bdelete(allocator);
    printf("Test case 1 passed\n");
}

// Test case 2: Allocation size larger than upper bound
void test_allocation_upper_bound() {
    Balloc allocator = bcreate(1024, 0, 10);
    void *mem2 = balloc(allocator, 8000);
    assert(mem2 == NULL && "Allocated memory larger than upper bound");
    bdelete(allocator);
    printf("Test case 2 passed\n");
}

// Test case 3: Size retrieval
void test_size_retrieval() {
    Balloc allocator = bcreate(1024, 0, 10);
    void *mem3 = balloc(allocator, 128);
    unsigned int size3 = bsize(allocator, mem3);
    assert(size3 == 128 && "Incorrect size retrieved");
    bfree(allocator, mem3);
    bdelete(allocator);
    printf("Test case 3 passed\n");
}

void test4() {
    // create an allocator
    Balloc allocator = bcreate(1024, 0, 10);
    // request all the memory from the allocator
    void* mem = balloc(allocator, 1024);
    // assert that the size of the allocation is 1024
    assert(bsize(allocator, mem) == 1024);
    // check that the Freelist is empty
    bprint(allocator);
    // check that all bits in the bitmap are set to '1'
    // deallocate the memory
    bfree(allocator, mem);
    // check that the Freelist has one block of max size
    bprint(allocator);
    // check that all bits in the bitmap are set to '0'
    // delete the allocator
    bdelete(allocator);
}

// Main function to run all tests
int main() {
    test_basic_allocation();
    test_allocation_upper_bound();
    test_size_retrieval();
    test4();
    return 0;
}
