// #include "../include/mat2.h"

// // Multiply matrix by vector2
// vec2 mat2_mult_vec2(mat2 M, vec2 v) {
//   vec2 r;
//   r.x = v.x * M.m00 + v.y * M.m10;
//   r.y = v.x * M.m01 + v.y * M.m11;
//   return r;
// }

// // Multiply two matrices
// mat2 mat2_mult(mat2 A, mat2 B) {
//   mat2 C;
//   C.m00 = A.m00 * B.m00 + A.m01 * B.m10;
//   C.m01 = A.m00 * B.m01 + A.m01 * B.m11;
//   C.m10 = A.m10 * B.m00 + A.m11 * B.m10;
//   C.m11 = A.m10 * B.m01 + A.m11 * B.m11;
//   return C;
// }

#include "../include/Mat2.h"

// =========================
// Constructors
// =========================

Mat2::Mat2() : m00(0), m01(0), m10(0), m11(0) {}

Mat2::Mat2(float m00, float m01, float m10, float m11)
    : m00(m00), m01(m01), m10(m10), m11(m11) {}

// =========================
// Matrix * Vector
// =========================

Vec2 Mat2::operator*(const Vec2 &v) const {
  return Vec2(v.x * m00 + v.y * m10, v.x * m01 + v.y * m11);
}

// =========================
// Matrix * Matrix
// =========================

Mat2 Mat2::operator*(const Mat2 &B) const {
  const Mat2 &A = *this;

  return Mat2(A.m00 * B.m00 + A.m01 * B.m10, A.m00 * B.m01 + A.m01 * B.m11,
              A.m10 * B.m00 + A.m11 * B.m10, A.m10 * B.m01 + A.m11 * B.m11);
}