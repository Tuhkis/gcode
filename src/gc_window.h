#ifndef GC_WINDOW_H
#define GC_WINDOW_H

void gc_create_window(int w, int h, char *title);
void gc_window_events();
void gc_close_window();
void gc_display_swap();
void gc_set_window_title(char *title);

#endif
