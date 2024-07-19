#ifndef GC_GL_H
#define GC_GL_H

#include "gc_os.h"

#ifdef OS_UNIX
#include "GL/gl.h"
#endif

/* X-macro bullshit go!!!! */
#define GC_OGL_FUNCTIONS_X_MACRO() \
  X(void, glGenBuffers, GLsizei, GLuint*) \
  X(void, glBindBuffer, GLenum, GLuint) \
  X(void, glBufferData, GLenum, GLsizeiptr, const void*, GLenum) \
  X(GLuint, glCreateShader, GLenum) \
  X(void, glShaderSource(GLuint , GLsizei, const GLchar **, const GLint *) \
  X(void, glCompileShader, GLuint) \
  X(GLuint glCreateProgram, void) \
  X(void, glAttachShader, GLuint, GLuint) \
  X(void, glLinkProgram, GLuint) \
  X(void, glUseProgram, GLuint) \
  X(void, glDeleteShader, GLuint) \
  X(void, glVertexAttribPointer, GLuint, GLint, GLenum, GLboolean, GLsizei, const void *) \
  X(void, glEnableVertexAttribArray, GLuint) \
  X(void, glGenVertexArrays, GLsizei, GLuint*) \
  X(void, glBindVertexArray, GLuint)

#define X(ret, name, ...) \
  ret (*name)(...);

GC_OGL_FUNCTIONS_X_MACRO()

#undef X

void *gc_load_gl_function(const char *name);

#endif
