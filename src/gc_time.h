#ifndef GC_TIME_H
#define GC_TIME_H

#include "stdint.h"

#define GC_FPS2US(v) (1000000.f / v)
#define GC_S2FPS(dt) (1.f / dt)

typedef uint64_t gc_time_t;

gc_time_t gc_now();
void gc_usleep(gc_time_t d);

#endif
