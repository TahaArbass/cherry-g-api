// #include "../include/vec2.h"
// #include <math.h>

// // Scalar operations
// vec2 vec2_subf(vec2 v, float scalar) {
//   v.x -= scalar;
//   v.y -= scalar;
//   return v;
// }

// vec2 vec2_addf(vec2 v, float scalar) {
//   v.x += scalar;
//   v.y += scalar;
//   return v;
// }

// vec2 vec2_multf(vec2 v, float scalar) {
//   v.x *= scalar;
//   v.y *= scalar;
//   return v;
// }

// vec2 vec2_divf(vec2 v, float scalar) {
//   v.x /= scalar;
//   v.y /= scalar;
//   return v;
// }

// // Vector operations
// vec2 vec2_sub(vec2 a, vec2 b) {
//   vec2 c = {a.x - b.x, a.y - b.y};
//   return c;
// }

// vec2 vec2_add(vec2 a, vec2 b) {
//   vec2 c = {a.x + b.x, a.y + b.y};
//   return c;
// }

// vec2 vec2_mult(vec2 a, vec2 b) {
//   vec2 c = {a.x * b.x, a.y * b.y};
//   return c;
// }

// vec2 vec2_div(vec2 a, vec2 b) {
//   vec2 c = {a.x / b.x, a.y / b.y};
//   return c;
// }

// vec2 vec2_cos(vec2 v) {
//   vec2 r;
//   r.x = cosf(v.x);
//   r.y = cosf(v.y);
//   return r;
// }
// vec2 vec2_sin(vec2 v) {
//   vec2 r;
//   r.x = sinf(v.x);
//   r.y = sinf(v.y);
//   return r;
// }

// vec2 vec2_max(vec2 a, vec2 b) {
//   return (vec2){fmaxf(a.x, b.x), fmaxf(a.y, b.y)};
// }

// float vec2_length(vec2 v) { return sqrtf(v.x * v.x + v.y * v.y); }

#include "../include/Vec2.h"
#include <algorithm>
#include <cmath>

// =========================
// Constructors
// =========================

Vec2::Vec2() : x(0.0f), y(0.0f) {}
Vec2::Vec2(float x, float y) : x(x), y(y) {}

// =========================
// Scalar Operators
// =========================

Vec2 Vec2::operator+(float scalar) const {
  return Vec2(x + scalar, y + scalar);
}

Vec2 Vec2::operator-(float scalar) const {
  return Vec2(x - scalar, y - scalar);
}

Vec2 Vec2::operator*(float scalar) const {
  return Vec2(x * scalar, y * scalar);
}

Vec2 Vec2::operator/(float scalar) const {
  return Vec2(x / scalar, y / scalar);
}

// =========================
// Vector Operators
// =========================

Vec2 Vec2::operator+(const Vec2 &other) const {
  return Vec2(x + other.x, y + other.y);
}

Vec2 Vec2::operator-(const Vec2 &other) const {
  return Vec2(x - other.x, y - other.y);
}

Vec2 Vec2::operator*(const Vec2 &other) const {
  return Vec2(x * other.x, y * other.y);
}

Vec2 Vec2::operator/(const Vec2 &other) const {
  return Vec2(x / other.x, y / other.y);
}

// =========================
// Compound Assignment
// =========================

Vec2 &Vec2::operator+=(const Vec2 &other) {
  x += other.x;
  y += other.y;
  return *this;
}

Vec2 &Vec2::operator-=(const Vec2 &other) {
  x -= other.x;
  y -= other.y;
  return *this;
}

Vec2 &Vec2::operator*=(float scalar) {
  x *= scalar;
  y *= scalar;
  return *this;
}

Vec2 &Vec2::operator/=(float scalar) {
  x /= scalar;
  y /= scalar;
  return *this;
}

// =========================
// Math Functions
// =========================

Vec2 Vec2::cos() const { return Vec2(std::cos(x), std::cos(y)); }

Vec2 Vec2::sin() const { return Vec2(std::sin(x), std::sin(y)); }

Vec2 Vec2::max(const Vec2 &a, const Vec2 &b) {
  return Vec2(std::max(a.x, b.x), std::max(a.y, b.y));
}

float Vec2::length() const { return std::sqrt(x * x + y * y); }