#include "../include/vec4.h"

// Scalar operations
vec4 vec4_subf(vec4 v, float s) {
  v.x -= s;
  v.y -= s;
  v.z -= s;
  v.w -= s;
  return v;
}

vec4 vec4_addf(vec4 v, float s) {
  v.x += s;
  v.y += s;
  v.z += s;
  v.w += s;
  return v;
}

vec4 vec4_multf(vec4 v, float s) {
  v.x *= s;
  v.y *= s;
  v.z *= s;
  v.w *= s;
  return v;
}

vec4 vec4_divf(vec4 v, float s) {
  v.x /= s;
  v.y /= s;
  v.z /= s;
  v.w /= s;
  return v;
}

// Vector operations
vec4 vec4_sub(vec4 a, vec4 b) {
  vec4 c = {a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w};
  return c;
}

vec4 vec4_add(vec4 a, vec4 b) {
  vec4 c = {a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w};
  return c;
}

vec4 vec4_mult(vec4 a, vec4 b) {
  vec4 c = {a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w};
  return c;
}

vec4 vec4_div(vec4 a, vec4 b) {
  vec4 c = {a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w};
  return c;
}