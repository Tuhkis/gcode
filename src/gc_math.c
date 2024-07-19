#include "gc_math.h"

float gc_exp2f(float p)
{
  if(p < -126.f) p = -126.f;
  int w = (int)p;
  float z = p - (float)w;
  if(p < 0.f) z += 1.f;
  union { uint32_t i; float f; } v = { (uint32_t)((1 << 23) * (p + 121.2740575f + 27.7280233f / (4.84252568f - z) - 1.49012907f * z)) };
  return v.f;
}

/* Framrate independent lerp... hopefully... */
float gc_lerpf(float a, float b, float dt, float ht)
{
#define EPSILON (.05f)
  if (a > b - EPSILON && a < b + EPSILON) return b;
  else return b + (a - b) * gc_exp2f(-dt / ht);
#undef EPSILON
}

float gc_qlerpf(float a, float b, float dt, float scale)
{
#define EPSILON (.05f)
  if (a > b - EPSILON && a < b + EPSILON) return b;
  else return a + (b - a) * (1 - gc_exp2f(-scale * dt));
#undef EPSILON
}
