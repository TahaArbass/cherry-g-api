// #ifndef VEC4_H
// #define VEC4_H

// typedef struct {
//   float x;
//   float y;
//   float z;
//   float w;
// } vec4;

// // Scalar operations
// vec4 vec4_subf(vec4 v, float s);
// vec4 vec4_addf(vec4 v, float s);
// vec4 vec4_multf(vec4 v, float s);
// vec4 vec4_divf(vec4 v, float s);

// // Vector operations
// vec4 vec4_sub(vec4 a, vec4 b);
// vec4 vec4_add(vec4 a, vec4 b);
// vec4 vec4_mult(vec4 a, vec4 b);
// vec4 vec4_div(vec4 a, vec4 b);

// vec4 vec4_cos(vec4 v);
// vec4 vec4_sin(vec4 v);
// vec4 vec4_pow(vec4 a, vec4 b);
// vec4 vec4_tanh(vec4 a);

// #endif

#ifndef VEC4_H
#define VEC4_H

#include <algorithm>
#include <cmath>


class Vec4 {
public:
  float x, y, z, w;

  // Constructors
  Vec4();
  Vec4(float x, float y, float z, float w);

  // =========================
  // Scalar Operators
  // =========================
  Vec4 operator+(float s) const;
  Vec4 operator-(float s) const;
  Vec4 operator*(float s) const;
  Vec4 operator/(float s) const;

  // =========================
  // Vector Operators
  // =========================
  Vec4 operator+(const Vec4 &other) const;
  Vec4 operator-(const Vec4 &other) const;
  Vec4 operator*(const Vec4 &other) const;
  Vec4 operator/(const Vec4 &other) const;

  // =========================
  // Compound Assignment
  // =========================
  Vec4 &operator+=(const Vec4 &other);
  Vec4 &operator-=(const Vec4 &other);
  Vec4 &operator*=(float s);
  Vec4 &operator/=(float s);

  // =========================
  // Math Functions
  // =========================
  Vec4 cos() const;
  Vec4 sin() const;
  Vec4 tanh() const;

  static Vec4 pow(const Vec4 &a, const Vec4 &b);
};

#endif