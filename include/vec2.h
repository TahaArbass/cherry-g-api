#ifndef VEC2_H
#define VEC2_H

typedef struct {
  float x;
  float y;
} vec2;

// Scalar operations
vec2 vec2_subf(vec2 vec, float scalar);
vec2 vec2_addf(vec2 vec, float scalar);
vec2 vec2_multf(vec2 vec, float scalar);
vec2 vec2_divf(vec2 vec, float scalar);

// Vector operations
vec2 vec2_sub(vec2 a, vec2 b);
vec2 vec2_add(vec2 a, vec2 b);
vec2 vec2_mult(vec2 a, vec2 b);
vec2 vec2_div(vec2 a, vec2 b);

#endif