#include "gc_file.h"
#include "gc_os.h"
#include "gc_mem.h"
#include "gc_util.h"

int gc_read_file_data(const char *path, size_t *sz, char **data)
{
#ifdef OS_LINUX
#include "stdio.h"
#include "fcntl.h"
#include "sys/types.h"
#include "sys/stat.h"
#include "unistd.h"
#include "sys/mman.h"
  struct stat s;
  int fd = open(path, O_RDONLY | S_IRUSR);
  int status = fstat(fd, &s);
  GC_DISCARD(status);
  int pagesize = getpagesize();
  *sz = s.st_size;
  *sz += pagesize - (*sz % pagesize);
  *data = (char *)mmap(NULL, *sz, PROT_READ, MAP_FILE | MAP_PRIVATE, fd, 0);
  if (*data == (void *)-1) return GC_FAILURE;
  else gc_mapped_memory_sz += *sz;
  close(fd);
#endif
  return GC_SUCCESS;
}
