#include "../include/vec2.h"
#include <math.h>

// Scalar operations
vec2 vec2_subf(vec2 v, float scalar) {
  v.x -= scalar;
  v.y -= scalar;
  return v;
}

vec2 vec2_addf(vec2 v, float scalar) {
  v.x += scalar;
  v.y += scalar;
  return v;
}

vec2 vec2_multf(vec2 v, float scalar) {
  v.x *= scalar;
  v.y *= scalar;
  return v;
}

vec2 vec2_divf(vec2 v, float scalar) {
  v.x /= scalar;
  v.y /= scalar;
  return v;
}

// Vector operations
vec2 vec2_sub(vec2 a, vec2 b) {
  vec2 c = {a.x - b.x, a.y - b.y};
  return c;
}

vec2 vec2_add(vec2 a, vec2 b) {
  vec2 c = {a.x + b.x, a.y + b.y};
  return c;
}

vec2 vec2_mult(vec2 a, vec2 b) {
  vec2 c = {a.x * b.x, a.y * b.y};
  return c;
}

vec2 vec2_div(vec2 a, vec2 b) {
  vec2 c = {a.x / b.x, a.y / b.y};
  return c;
}

vec2 vec2_max(vec2 a, vec2 b) {
  return (vec2){fmaxf(a.x, b.x), fmaxf(a.y, b.y)};
}

float vec2_length(vec2 v) { return sqrtf(v.x * v.x + v.y * v.y); }