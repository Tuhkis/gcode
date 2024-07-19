/**
 * Open an X11 window and initialise a modern ogl context.
 */

// weird issues are afoot.
#ifndef locale_t
typedef int locale_t;
#endif
#include "string.h"
#include "stdbool.h"
#include "X11/Xlib.h"
#include "X11/Xutil.h"
#include "X11/keysymdef.h"
#include "GL/glx.h"

#include "gc_main.h"

typedef GLXContext (*glXCreateContextAttribsARBProc)(Display *, GLXFBConfig, GLXContext, int, const int *);

static Display *display;
static Window window;
static Screen *screen;
static int screenID;
static XEvent e;
static GLXContext glctx;
XVisualInfo* visual;
static XSetWindowAttributes window_attribs;
static Atom atom_wm_delete_window;
static int framebuffers = 0;

static int extension_supported(const char *extList, const char *extension) {
	return strstr(extList, extension) != 0;
}

void gc_set_window_title(char *title)
{
  XStoreName(display, window, (char *)title);
}

void gc_create_window(int w, int h, char *title)

{
  display = XOpenDisplay(NULL);
  if (!display) return;
  screen = DefaultScreenOfDisplay(display);
  screenID = DefaultScreen(display);

  GLint glx_major, glx_minor = 0;
  glXQueryVersion(display, &glx_major, &glx_minor);
  if (glx_major <= 1 && glx_minor < 3)
  {
     puts("Need GLX 1.3 or newer");
     XCloseDisplay(display);
  }
  GLint glx_attribs[] = {
    GLX_X_RENDERABLE, True,
		GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
		GLX_RENDER_TYPE, GLX_RGBA_BIT,
		GLX_X_VISUAL_TYPE, GLX_TRUE_COLOR,
		GLX_RED_SIZE, 8,
		GLX_GREEN_SIZE, 8,
		GLX_BLUE_SIZE, 8,
		GLX_ALPHA_SIZE, 8,
		GLX_DEPTH_SIZE, 24,
		GLX_STENCIL_SIZE, 8,
		GLX_DOUBLEBUFFER, True,
		None
  };

  static GLXFBConfig *framebuffer_config;
  framebuffer_config = glXChooseFBConfig(display, screenID, glx_attribs, &framebuffers);
  if (!framebuffer_config)
  {
    puts("shit.");
  }

  static int best_fbc = -1;
  static int worst_fbc = -1;
  static int best_num_samp = -1;
  static int worst_num_samp = 999;

  for (int i = 0; i < framebuffers; ++i)
  {
    XVisualInfo *vinfo = glXGetVisualFromFBConfig(display, framebuffer_config[i]);
    if (vinfo != NULL)
    {
      static int samp_buf;
      static int samples;
      glXGetFBConfigAttrib(display, framebuffer_config[i], GLX_SAMPLE_BUFFERS, &samp_buf);
      glXGetFBConfigAttrib(display, framebuffer_config[i], GLX_SAMPLES, &samples);
      if ( best_fbc < 0 || (samp_buf && samples > best_num_samp) ) {
				best_fbc = i;
				best_num_samp = samples;
			}
			if ( worst_fbc < 0 || !samp_buf || samples < worst_num_samp )
				worst_fbc = i;
			worst_num_samp = samples;
    }
    XFree(vinfo);
  }
  GLXFBConfig best_framebuffer_config = framebuffer_config[best_fbc];
  XFree(framebuffer_config);

  visual = glXGetVisualFromFBConfig(display, best_framebuffer_config);
  if (visual == NULL || screenID != visual->screen)
  {
    puts("Shit");
  }

  window_attribs.border_pixel = BlackPixel(display, screenID);
  window_attribs.background_pixel = WhitePixel(display, screenID);
  window_attribs.override_redirect = True;
  window_attribs.colormap = XCreateColormap(display, RootWindow(display, screenID), visual->visual, AllocNone);
  window_attribs.event_mask = ExposureMask;
  window = XCreateWindow(display,
    RootWindow(display, screenID),
    0, 0, w, h,
    0, visual->depth, InputOutput, visual->visual,
    CWBackPixel | CWColormap | CWBorderPixel | CWEventMask,
    &window_attribs
  );

  glXCreateContextAttribsARBProc glXCreateContextAttribsARB = NULL;
  glXCreateContextAttribsARB = (glXCreateContextAttribsARBProc)
    glXGetProcAddressARB((const GLubyte *)"glXCreateContextAttribsARB");

  int gl_context_attribs[] = {
  	GLX_CONTEXT_MAJOR_VERSION_ARB, 3,
  	GLX_CONTEXT_MINOR_VERSION_ARB, 3,
    GLX_CONTEXT_FLAGS_ARB, GLX_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
		None
  };
  const char *glx_exts = glXQueryExtensionsString(display,  screenID);
	if (!extension_supported(glx_exts, "GLX_ARB_create_context")) {
		glctx = glXCreateNewContext(display, best_framebuffer_config, GLX_RGBA_TYPE, 0, True);
	}
	else {
		glctx = glXCreateContextAttribsARB(display, best_framebuffer_config, 0, true, gl_context_attribs);
	}
	XSync(display, False);
  if (!glXIsDirect(display, glctx))
  {
    puts("shit");
  }
  glXMakeCurrent(display, window, glctx);

  gc_set_window_title(title);
  atom_wm_delete_window = XInternAtom(display, "WM_DELETE_WINDOW", False);
  XSetWMProtocols(display, window, &atom_wm_delete_window, 1);
  XSync(display, False);
  XClearWindow(display, window);
  XMapRaised(display, window);
}

void gc_window_events()
{
  if (XPending(display) > 0)
  {
    XNextEvent(display, &e);
		switch (e.type)
    {
      case ClientMessage: GC_FALLTHROUGH
        if (e.xclient.data.l[0] != (long int)atom_wm_delete_window) break;
      case DestroyNotify:
        gc_close_app();
        break;
      default:
        break;
    }
  }
}

void gc_close_window()
{
  XFree(visual);
  XFreeColormap(display, window_attribs.colormap);
  XDestroyWindow(display, window);
  XFree(screen);

  // Closing display segfaults?
  // XCloseDisplay(display);
}

void gc_display_swap()
{
  glXSwapBuffers(display, window);
}

void *gc_load_gl_function(const char *name)
{
  return glXGetProcAddressARB((const GLubyte*)name);
}
