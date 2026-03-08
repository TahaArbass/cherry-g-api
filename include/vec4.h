#ifndef VEC4_H
#define VEC4_H

typedef struct {
  float x;
  float y;
  float z;
  float w;
} vec4;

// Scalar operations
vec4 vec4_subf(vec4 v, float s);
vec4 vec4_addf(vec4 v, float s);
vec4 vec4_multf(vec4 v, float s);
vec4 vec4_divf(vec4 v, float s);

// Vector operations
vec4 vec4_sub(vec4 a, vec4 b);
vec4 vec4_add(vec4 a, vec4 b);
vec4 vec4_mult(vec4 a, vec4 b);
vec4 vec4_div(vec4 a, vec4 b);

#endif