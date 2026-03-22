// #ifndef MAT2_H
// #define MAT2_H

// #include "vec2.h"

// typedef struct {
//   float m00, m01;
//   float m10, m11;
// } mat2;

// vec2 mat2_mult_vec2(mat2 M, vec2 v);
// mat2 mat2_mult(mat2 A, mat2 B);

// #endif

#ifndef MAT2_H
#define MAT2_H

#include "Vec2.h"

class Mat2 {
public:
  float m00, m01;
  float m10, m11;

  // Constructors
  Mat2();
  Mat2(float m00, float m01, float m10, float m11);

  // =========================
  // Matrix Operations
  // =========================
  Mat2 operator*(const Mat2 &other) const;

  // =========================
  // Matrix-Vector Multiplication
  // =========================
  Vec2 operator*(const Vec2 &v) const;
};

#endif