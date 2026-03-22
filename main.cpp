// #include "include/mat2.h"
// #include "include/perlin.h"
// #include "include/vec2.h"
// #include "include/vec4.h"
// #include <math.h>
// #include <stdio.h>

#include "include/Mat2.h"
#include "include/Vec2.h"
#include "include/Vec4.h"
#include "include/perlin.h"


#include <cmath>
#include <cstdio>

Vec4 shader1(Vec2 r, Vec2 FC, Vec4 o, float t);
Vec4 shader2(Vec2 r, Vec2 FC, Vec4 o, float t);

int main() {
  int frames = 60, frameRate = 60;
  char buf[256];
  for (int frame = 0; frame < frames; frame++) {
    snprintf(buf, sizeof(buf), "output/output-%02d.ppm", frame);
    const char *outputPath = buf;
    const int scale = 60;
    // .ppm starts as a text format then switch to binary format
    FILE *file = fopen(outputPath, "wb");
    int w = 16 * scale, h = 9 * scale;
    fprintf(file, "P6\n%d %d\n255\n", w, h);

    Vec2 r((float)w, (float)h); // screen res
    for (int y = 0; y < h; y++) {
      for (int x = 0; x < w; x++) {
        Vec2 FC((float)x, (float)y);        // pixel coordinate
        Vec4 o(0, 0, 0, 0);                 // output
        float t = (float)frame / frameRate; // time

        // // this shader's eq needs more testing due to complexity
        // o = shader1(r, FC, o, t);
        o = shader2(r, FC, o, t);
        fputc(o.x * 255, file);
        fputc(o.y * 255, file);
        fputc(o.z * 255, file);
      }
    }
    fclose(file);
    printf("Generated %s\n", outputPath);
  }

  return 0;
}

/*
 * Reference function in GLSL and we are translating it into c
 *
 * vec2 p = (FC.xy - r * 0.5) / r.y * mat2(8, -6, 6, 8);
 * vec2 v;
 * float f = 3.0 + snoise2D(p + vec2(t * 7.0, 0.0));
 * for (float i = 0.0; i < 50.0; i++) {
 *     o += (cos(sin(i) * vec4(1, 2, 3, 1)) + 1.0)
 *          * exp(sin(i * i + t))
 *          / length(max(v, vec2(v.x * f * 0.02, v.y)));
 *     v = p + cos(i * i + (t + p.x * 0.1) * 0.03 + i * vec2(11, 9))
 * * 5.0;
 * }
 * o = tanh(pow(o / 1e2, vec4(1.5)));
 */
// vec4 shader1(vec2 r, vec2 FC, vec4 o, float t) {
//   vec2 p = vec2_divf(vec2_sub(FC, vec2_multf(r, 0.5f)), r.y);
//   mat2 M = {8, -6, 6, 8}; // 2x2 matrix
//   p = mat2_mult_vec2(M, p);
//   vec2 v = {0.0f, 0.0f};
//   float f = 3.0f + perlin2d(p.x + t * 7.0f, p.y, 0.1f, 4);

//   for (float i = 0; i++ < 50.0f; i++) {
//     vec4 tmp = {1, 2, 3, 1};
//     vec2 tmp1 = {v.x * f * 0.2f, v.y};

//     // parts of the full equation then they are added to the output
//     vec4 tmp2 = vec4_addf(vec4_cos(vec4_multf(tmp, sin(i))), 1.0f);
//     vec4 tmp3 = vec4_multf(tmp2, exp(sin(i * i + t)));
//     float length = vec2_length(vec2_max(v, tmp1));
//     o = vec4_add(o, vec4_divf(tmp3, length));

//     // updating v
//     v = vec2_add(
//         p, vec2_multf(vec2_cos(vec2_addf(vec2_multf((vec2){11.0f, 9.0f}, i),
//                                          i * i + (t + p.x * 0.1f) * 0.03f)),
//                       5.0f));
//   }

//   vec4 oneAndHalf = {1.5f, 1.5f, 1.5f, 1.5f};
//   o = vec4_tanh(vec4_pow(vec4_divf(o, 1e2), oneAndHalf));
//   return o;
// }

Vec4 shader1(Vec2 r, Vec2 FC, Vec4 o, float t) {
  Vec2 p = (FC - r * 0.5f) / r.y;

  Mat2 M(8, -6, 6, 8);
  p = M * p;

  Vec2 v(0.0f, 0.0f);

  float f = 3.0f + perlin2d(p.x + t * 7.0f, p.y, 0.1f, 4);

  for (float i = 0; i < 50.0f; i++) {
    Vec4 tmp(1, 2, 3, 1);
    Vec2 tmp1(v.x * f * 0.2f, v.y);

    Vec4 tmp2 = (tmp * std::sin(i)).cos() + 1.0f;
    Vec4 tmp3 = tmp2 * std::exp(std::sin(i * i + t));

    float len = Vec2::max(v, tmp1).length();

    o += tmp3 / len;

    v = p + (Vec2(11.0f, 9.0f) * i + (i * i + (t + p.x * 0.1f) * 0.03f)).cos() *
                5.0f;
  }

  Vec4 oneAndHalf(1.5f, 1.5f, 1.5f, 1.5f);

  o = Vec4::pow(o / 1e2f, oneAndHalf).tanh();

  return o;
}

/*
 * vec2 p=(FC.xy*2.-r)/r.y;
 * o+=.1/abs(length(p)-.5+.01/(p.x-p.y));
 */
// vec4 shader2(vec2 r, vec2 FC, vec4 o, float t) {
//   vec2 p = vec2_divf(vec2_sub(vec2_multf(FC, 2.0f), r), r.y);
//   float denom = p.x - p.y;
//   if (fabs(denom) < 1e-6f)
//     denom = (denom < 0 ? -1e-6f : 1e-6f);
//   float val = 0.1f / fabs(vec2_length(p) - 0.5f + 0.01f / denom);
//   o = vec4_addf(o, val);
//   return o;
// }
Vec4 shader2(Vec2 r, Vec2 FC, Vec4 o, float t) {
  Vec2 p = (FC * 2.0f - r) / r.y;

  float denom = p.x - p.y;
  if (std::fabs(denom) < 1e-6f)
    denom = (denom < 0 ? -1e-6f : 1e-6f);

  float val = 0.1f / std::fabs(p.length() - 0.5f + 0.01f / denom);

  o = o + val;

  return o;
}