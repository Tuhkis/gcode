#include "stdio.h"
#include "stdlib.h"
#include "math.h"

#include "gc_main.h"
#include "gc_window.h"
#include "gc_time.h"
#include "gc_mem.h"
#include "gc_util.h"
#include "gc_math.h"
#include "gc_gfx.h"
#include "gc_style.h"
#include "gc_file.h"

MAIN(argc, argv)
  GC_DISCARD(argc);
  GC_DISCARD(argv);

  gc_create_window(1200, 800, "Title");

  char *file_data = NULL;
  size_t sz;
  gc_read_file_data("src/gc_main.c", &sz, &file_data);
  puts(file_data);
  gc_unmap(file_data, sz);

  gc_colour_t col = {0};

  gc_time_t now, prev = 0;
  for (;1;)
  {
    now = gc_now();
    gc_usleep(GC_FPS2US(60));
    gc_window_events();
    float dt = (float)(now - prev) / 1000000.f;
    dt = dt > 0.1 ? 0 : dt;

    col.r = gc_qlerpf(col.r, 0.4, dt, 0.1);
    col.g = gc_qlerpf(col.g, 0.6, dt, 0.5);
    col.b = gc_qlerpf(col.b, 1, dt, 2);

    gc_set_clear_colour(col);
    gc_clear();

    gc_display_swap();
    prev = now;
  }
  gc_close_app();
  return 0;
END_MAIN


void gc_close_app()
{
  gc_close_window();
  if (gc_mapped_memory_sz != 0)
  {
    printf("%f mb was not unmapped.\n", gc_mapped_memory_sz / 1024.f);
  }
  gc_exit(0);
}
