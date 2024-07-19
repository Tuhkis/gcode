#include "gc_os.h"

#ifdef OS_LINUX
#include "sys/mman.h"
#endif

#include "gc_mem.h"

/* NOTE: gc is not for garbage collection. */

size_t gc_mapped_memory_sz = 0;

void *gc_map(size_t sz)
{
#ifdef OS_UNIX
  void *ret = mmap(NULL, sz, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, 0, 0);
  if (ret == (void *)-1) return NULL;
  gc_mapped_memory_sz += sz;
  return ret;
#endif
}

int gc_unmap(void *p, size_t sz)
{
  #ifdef OS_UNIX
  int success = munmap(p, sz) == 0;
  if (success)
    gc_mapped_memory_sz -= sz;
  return success;
#endif
}
