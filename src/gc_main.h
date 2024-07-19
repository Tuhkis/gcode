#ifndef GC_MAIN_H
#define GC_MAIN_H

#include "gc_os.h"

void gc_close_app();

#ifndef OS_WIN
#define MAIN(argc, argv) int main(int argc, char **argv) {
#define END_MAIN }
#else
shit winmain stuff
#define MAIN(argc, argv) int WinMain(...
#define END_MAIN }
#endif

#endif
