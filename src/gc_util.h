#ifndef GC_UTIL_H
#define GC_UTIL_H

#include "gc_os.h"

#define GC_DISCARD(e) ((void)e)
#define GC_FALLTHROUGH
#define GC_SUCCESS (1)
#define GC_FAILURE (0)

static inline void gc_exit(int c)
{
#ifdef OS_UNIX
#include "stdlib.h"
  exit(c);
#endif
}

#endif
