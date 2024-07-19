#ifndef GC_FILE_H
#define GC_FILE_H

#include "stdlib.h"

/**
 * Must be manually unmapped
 */
int gc_read_file_data(const char *path, size_t *sz, char **data);

#endif
