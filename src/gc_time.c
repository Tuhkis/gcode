#include "gc_os.h"
#include "gc_time.h"

gc_time_t gc_now()
{
#ifdef OS_UNIX
#include "time.h"
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  return ts.tv_sec * 1000000UL + ts.tv_nsec / 1000;
#endif
}
void gc_usleep(gc_time_t d)
{
#ifdef OS_UNIX
#include "errno.h"
#ifndef nanosleep
  int nanosleep(const struct timespec *req, struct timespec *rem);
#endif
  struct timespec ts;
  ts.tv_sec = d / 1000000;
  ts.tv_nsec = (d % 1000000) * 1000;
  for (;(nanosleep(&ts, &ts) == -1) && (errno == EINTR););
#endif
}
