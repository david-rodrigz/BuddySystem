#include <string.h>
#include <stdlib.h>
#include "balloc.h"
#include "utils.h"
#include "freelist.h"
#include "bbm.h"

struct BallocStruct {
    unsigned int size;
    int l;
    int u;
    BBM bitmap;
    FreeList freelist;
};

Balloc bcreate(unsigned int size, int l, int u) {
    struct BallocStruct *pool = malloc(sizeof(struct BallocStruct));
    if (pool == NULL) {
        return NULL;
    }
    pool->size = size;
    pool->l = l;
    pool->u = u;
    pool->bitmap = bbmcreate(size, l);
    pool->freelist = freelistcreate(size, l, u);
    return pool;
}

void bdelete(Balloc pool) {
    struct BallocStruct *p = (struct BallocStruct *)pool;
    bbmdelete(p->bitmap);
    freelistdelete(p->freelist, p->l, p->u);
    free(p);
}

void *balloc(Balloc pool, unsigned int size) {
    struct BallocStruct *p = (struct BallocStruct *)pool;
    int e = size2e(size);
    if (e < p->l || e > p->u) {
        return NULL;
    }
    void *mem = freelistalloc(p->freelist, p->bitmap, e, p->l);
    if (mem == NULL) {
        return NULL;
    }
    bbmset(p->bitmap, pool, mem, e);
    return mem;
}

void bfree(Balloc pool, void *mem) {
    struct BallocStruct *p = (struct BallocStruct *)pool;
    int e = size2e(bsize(pool, mem));
    freelistfree(p->freelist, pool, mem, e, p->l);
    bbmclr(p->bitmap, pool, mem, e);
}

unsigned int bsize(Balloc pool, void *mem) {
    struct BallocStruct *p = (struct BallocStruct *)pool;
    int e = p->l;
    while (e2size(e) < (char *)mem - (char *)pool) {
        e++;
    }
    return e2size(e);
}

void bprint(Balloc pool) {
    struct BallocStruct *p = (struct BallocStruct *)pool;
    printf("Bitmap:\n");
    bbmprt(p->bitmap);
    printf("Freelist:\n");
    freelistprint(p->freelist, p->l, p->u);
}