#ifndef GC_GFX_H
#define GC_GFX_H

#include "gc_os.h"
#include "gc_style.h"

#ifdef OS_WIN
#define GC_GFX_D3D11
#else
#ifdef OS_MAC
#define GC_GFX_METAL
#else
#define GC_GFX_OGL
#include "gc_ogl.h"
#endif
#endif

#define gc_set_clear_color(c) gc_set_clear_colour((c))

typedef struct
{
  struct
  {
    float x, y;
  } pos;
  gc_colour_t colour;
} gc_render_vertex_t;

static inline void gc_set_clear_colour(gc_colour_t col)
{
#ifdef GC_GFX_OGL
  glClearColor(GC_COL2ARGS(col));
#endif
}

static inline void gc_clear(void)
{
#ifdef GC_GFX_OGL
  glClear(GL_COLOR_BUFFER_BIT);
#endif
}

#endif
