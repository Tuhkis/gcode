#include "gc_os.h"
#include "gc_gfx.h"

#include "gc_main.c"
#include "gc_mem.c"
#include "gc_time.c"
#include "gc_math.c"
#include "gc_file.c"
#include "gc_imgui.c"
#include "gc_ttf.c"

#ifdef OS_UNIX
#ifdef USE_WAYLAND
shit
#include "gc_wl_window.c"
#else
#include "gc_x11_window.c"
#endif
#endif

#ifdef GC_GFX_OGL
#include "gc_ogl_gfx.c"
#endif
