#ifndef MAT2_H
#define MAT2_H

#include "vec2.h"

typedef struct {
  float m00, m01;
  float m10, m11;
} mat2;

vec2 mat2_mult_vec2(mat2 M, vec2 v);
mat2 mat2_mult(mat2 A, mat2 B);

#endif