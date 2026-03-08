#include "../include/mat2.h"

// Multiply matrix by vector2
vec2 mat2_mul_vec2(mat2 M, vec2 v) {
  vec2 r;
  r.x = v.x * M.m00 + v.y * M.m10;
  r.y = v.x * M.m01 + v.y * M.m11;
  return r;
}

// Multiply two matrices
mat2 mat2_mul(mat2 A, mat2 B) {
  mat2 C;
  C.m00 = A.m00 * B.m00 + A.m01 * B.m10;
  C.m01 = A.m00 * B.m01 + A.m01 * B.m11;
  C.m10 = A.m10 * B.m00 + A.m11 * B.m10;
  C.m11 = A.m10 * B.m01 + A.m11 * B.m11;
  return C;
}