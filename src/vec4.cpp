// #include "../include/vec4.h"
// #include <math.h>

// // Scalar operations
// vec4 vec4_subf(vec4 v, float s) {
//   v.x -= s;
//   v.y -= s;
//   v.z -= s;
//   v.w -= s;
//   return v;
// }

// vec4 vec4_addf(vec4 v, float s) {
//   v.x += s;
//   v.y += s;
//   v.z += s;
//   v.w += s;
//   return v;
// }

// vec4 vec4_multf(vec4 v, float s) {
//   v.x *= s;
//   v.y *= s;
//   v.z *= s;
//   v.w *= s;
//   return v;
// }

// vec4 vec4_divf(vec4 v, float s) {
//   v.x /= s;
//   v.y /= s;
//   v.z /= s;
//   v.w /= s;
//   return v;
// }

// // Vector operations
// vec4 vec4_sub(vec4 a, vec4 b) {
//   vec4 c = {a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w};
//   return c;
// }

// vec4 vec4_add(vec4 a, vec4 b) {
//   vec4 c = {a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w};
//   return c;
// }

// vec4 vec4_mult(vec4 a, vec4 b) {
//   vec4 c = {a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w};
//   return c;
// }

// vec4 vec4_div(vec4 a, vec4 b) {
//   vec4 c = {a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w};
//   return c;
// }

// vec4 vec4_cos(vec4 v) {
//   vec4 r;
//   r.x = cosf(v.x);
//   r.y = cosf(v.y);
//   r.z = cosf(v.z);
//   r.w = cosf(v.w);
//   return r;
// }
// vec4 vec4_sin(vec4 v) {
//   vec4 r;
//   r.x = sinf(v.x);
//   r.y = sinf(v.y);
//   r.z = sinf(v.z);
//   r.w = sinf(v.w);
//   return r;
// }

// vec4 vec4_pow(vec4 a, vec4 b) {
//   return (vec4){powf(a.x, b.x), powf(a.y, b.y), powf(a.z, b.z), powf(a.w,
//   b.w)};
// }

// vec4 vec4_tanh(vec4 a) {
//   return (vec4){tanhf(a.x), tanhf(a.y), tanhf(a.z), tanhf(a.w)};
// }

#include "../include/Vec4.h"

// =========================
// Constructors
// =========================

Vec4::Vec4() : x(0), y(0), z(0), w(0) {}

Vec4::Vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

// =========================
// Scalar Operators
// =========================

Vec4 Vec4::operator+(float s) const { return Vec4(x + s, y + s, z + s, w + s); }

Vec4 Vec4::operator-(float s) const { return Vec4(x - s, y - s, z - s, w - s); }

Vec4 Vec4::operator*(float s) const { return Vec4(x * s, y * s, z * s, w * s); }

Vec4 Vec4::operator/(float s) const { return Vec4(x / s, y / s, z / s, w / s); }

// =========================
// Vector Operators
// =========================

Vec4 Vec4::operator+(const Vec4 &o) const {
  return Vec4(x + o.x, y + o.y, z + o.z, w + o.w);
}

Vec4 Vec4::operator-(const Vec4 &o) const {
  return Vec4(x - o.x, y - o.y, z - o.z, w - o.w);
}

Vec4 Vec4::operator*(const Vec4 &o) const {
  return Vec4(x * o.x, y * o.y, z * o.z, w * o.w);
}

Vec4 Vec4::operator/(const Vec4 &o) const {
  return Vec4(x / o.x, y / o.y, z / o.z, w / o.w);
}

// =========================
// Compound Assignment
// =========================

Vec4 &Vec4::operator+=(const Vec4 &o) {
  x += o.x;
  y += o.y;
  z += o.z;
  w += o.w;
  return *this;
}

Vec4 &Vec4::operator-=(const Vec4 &o) {
  x -= o.x;
  y -= o.y;
  z -= o.z;
  w -= o.w;
  return *this;
}

Vec4 &Vec4::operator*=(float s) {
  x *= s;
  y *= s;
  z *= s;
  w *= s;
  return *this;
}

Vec4 &Vec4::operator/=(float s) {
  x /= s;
  y /= s;
  z /= s;
  w /= s;
  return *this;
}

// =========================
// Math Functions
// =========================

Vec4 Vec4::cos() const {
  return Vec4(std::cos(x), std::cos(y), std::cos(z), std::cos(w));
}

Vec4 Vec4::sin() const {
  return Vec4(std::sin(x), std::sin(y), std::sin(z), std::sin(w));
}

Vec4 Vec4::tanh() const {
  return Vec4(std::tanh(x), std::tanh(y), std::tanh(z), std::tanh(w));
}

Vec4 Vec4::pow(const Vec4 &a, const Vec4 &b) {
  return Vec4(std::pow(a.x, b.x), std::pow(a.y, b.y), std::pow(a.z, b.z),
              std::pow(a.w, b.w));
}