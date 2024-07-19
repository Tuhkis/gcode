#ifndef GC_STYLE_H
#define GC_STYLE_H

#define GC_COL2ARGS(c) c.r, c.g, c.b, c.a

typedef struct
{
  float r, g, b, a;
} gc_colour_t;
typedef gc_colour_t gc_color_t;

typedef struct
{
  gc_colour_t bg0;
  gc_colour_t bg1;
} gc_style_t;

#endif
