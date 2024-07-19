#ifndef GC_MATH_H
#define GC_MATH_H

#define GC_MIN(a, m) ((a) > (m) ? (a) : (m))
#define GC_MAX(a, m) ((a) < (m) ? (a) : (m))
#define GC_CLAMP(a, min, max) ((a) < (min) ? (min) : \
  (a) > (max) ? (max) : (a))
#define GC_ABS(a) ((a) < 0 ? -(a) : (a))

typedef float gc_m4_t[4 * 4];

float gc_exp2f(float p);
float gc_lerpf(float a, float b, float dt, float ht);
float gc_qlerpf(float a, float b, float dt, float scale);

#endif
