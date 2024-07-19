#ifndef GC_MEM_H
#define GC_MEM_H

#include "stdlib.h"

extern size_t gc_mapped_memory_sz;

void *gc_map(size_t sz);
int gc_unmap(void *ptr, size_t sz);

#endif
