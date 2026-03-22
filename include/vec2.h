// #ifndef VEC2_H
// #define VEC2_H

// typedef struct {
//   float x;
//   float y;
// } vec2;

// // Scalar operations
// vec2 vec2_subf(vec2 v, float scalar);
// vec2 vec2_addf(vec2 v, float scalar);
// vec2 vec2_multf(vec2 v, float scalar);
// vec2 vec2_divf(vec2 v, float scalar);

// // Vector operations
// vec2 vec2_sub(vec2 a, vec2 b);
// vec2 vec2_add(vec2 a, vec2 b);
// vec2 vec2_mult(vec2 a, vec2 b);
// vec2 vec2_div(vec2 a, vec2 b);

// vec2 vec2_cos(vec2 v);
// vec2 vec2_sin(vec2 v);
// vec2 vec2_max(vec2 a, vec2 b);
// float vec2_length(vec2 v);

// #endif

#ifndef VEC2_H
#define VEC2_H

class Vec2 {
public:
  float x, y;

  // Constructors
  Vec2();
  Vec2(float x, float y);

  // =========================
  // Scalar Operators
  // =========================
  Vec2 operator+(float scalar) const;
  Vec2 operator-(float scalar) const;
  Vec2 operator*(float scalar) const;
  Vec2 operator/(float scalar) const;

  // =========================
  // Vector Operators
  // =========================
  Vec2 operator+(const Vec2 &other) const;
  Vec2 operator-(const Vec2 &other) const;
  Vec2 operator*(const Vec2 &other) const;
  Vec2 operator/(const Vec2 &other) const;

  // =========================
  // Compound Assignment
  // =========================
  Vec2 &operator+=(const Vec2 &other);
  Vec2 &operator-=(const Vec2 &other);
  Vec2 &operator*=(float scalar);
  Vec2 &operator/=(float scalar);

  // =========================
  // Math Functions
  // =========================
  Vec2 cos() const;
  Vec2 sin() const;
  static Vec2 max(const Vec2 &a, const Vec2 &b);
  float length() const;
};

#endif