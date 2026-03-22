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
Vec4 shader3(Vec2 r, Vec2 FC, Vec4 o, float t);

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
        // o = shader2(r, FC, o, t);
        o = shader3(r, FC, o, t);
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
Vec4 shader1(Vec2 r, Vec2 FC, Vec4 o, float t) {
  // Transform pixel coordinates to [-0.5,0.5] range and apply matrix
  Vec2 p = (FC - r * 0.5f) / r.y;
  Mat2 M(8, -6, 6, 8);
  p = M * p;

  Vec2 v(0.0f, 0.0f);

  // Normalize perlin noise to ~[0,1] (your noise may output 0-255)
  float f = 3.0f + perlin2d(p.x + t * 7.0f, p.y, 0.1f, 4) / 255.0f;

  for (float i = 0.0f; i < 50.0f; i += 1.0f) {
    // Base vector for color manipulation
    Vec4 tmp(1.0f, 2.0f, 3.0f, 1.0f);
    Vec2 tmp1(v.x * f * 0.02f, v.y); // Scale v for denominator

    // Compute color contribution
    Vec4 tmp2 = (tmp * std::sin(i)).cos() + 1.0f; // cos(sin(i)*tmp)+1
    Vec4 tmp3 =
        tmp2 * std::exp(std::sin(i * i + t)); // multiply by exp(sin(...))

    // Safe denominator: avoid division by zero
    float len = Vec2::max(v, tmp1).length();
    len = std::max(len, 1e-3f);

    o += tmp3 / len;

    // Update v for next iteration
    Vec2 arg = Vec2(11.0f, 9.0f) * i + (i * i + (t + p.x * 0.1f) * 0.03f);
    v = p + arg.cos() * 5.0f;
  }

  // Final scaling and non-linear mapping
  Vec4 oneAndHalf(1.5f, 1.5f, 1.5f, 1.5f);
  o = Vec4::pow(o / 100.0f, oneAndHalf).tanh();

  return o;
}

/*
 * vec2 p=(FC.xy*2.-r)/r.y;
 * o+=.1/abs(length(p)-.5+.01/(p.x-p.y));
 */
Vec4 shader2(Vec2 r, Vec2 FC, Vec4 o, float t) {
  Vec2 p = (FC * 2.0f - r) / r.y;

  float denom = p.x - p.y;
  denom = (std::fabs(denom) < 1e-6f) ? 1e-6f : denom;

  float val = 0.1f / std::fabs(p.length() - 0.5f + 0.01f / denom);

  o = o + val;

  return o;
}

Vec4 shader3(Vec2 r, Vec2 FC, Vec4 o, float t) {
  float z = 0.0f;
  for (int i = 0; i < 20; i++) { // i++ < 2e1
    // p = z * normalize(FC.rgb*2 - r.xyx)
    Vec4 fc_rgb(FC.x, FC.y, 0.0f, 0.0f);
    Vec4 r_xyx(r.x, r.y, r.x, 0.0f);
    Vec4 diff = fc_rgb * 2.0f - r_xyx;

    float len_diff =
        std::sqrt(diff.x * diff.x + diff.y * diff.y + diff.z * diff.z);
    Vec4 p = diff * (z / len_diff); // normalize and scale by z

    // p = vec3(atan(p.y/.2, p.x)*2., p.z/3., length(p.xy)-5.-z*0.2)
    float px = std::atan2(p.y, 0.2f) * 2.0f;
    float py = p.z / 3.0f;
    float pz = std::sqrt(p.x * p.x + p.y * p.y) - 5.0f - z * 0.2f;

    p = Vec4(px, py, pz, 0.0f);

    // inner loop: for(d=1.; d<7.; d++) p += sin(p.yzx*d + t + 0.3*i)/d
    for (int d = 1; d < 7; d++) {
      Vec4 tmp(p.y, p.z, p.x, 0.0f); // yzx swizzle
      Vec4 s(std::sin(tmp.x * d + t + 0.3f * i),
             std::sin(tmp.y * d + t + 0.3f * i),
             std::sin(tmp.z * d + t + 0.3f * i), 0.0f);
      p += s / float(d);
    }

    // z += d = length(vec4(0.4*cos(p) - 0.4, p.z))
    Vec4 tmp_cos = p.cos() * 0.4f - Vec4(0.4f, 0.4f, 0.4f, 0.0f);
    Vec4 len_vec(tmp_cos.x, tmp_cos.y, p.z, 0.0f);
    float d = std::sqrt(len_vec.x * len_vec.x + len_vec.y * len_vec.y +
                        len_vec.z * len_vec.z);
    z += d;

    // o += (cos(p.x + i*0.4 + z + vec4(6,1,2,0)) + 1) / d
    Vec4 offset(6.0f, 1.0f, 2.0f, 0.0f);
    Vec4 add_val =
        Vec4(p.x + i * 0.4f + z + offset.x, p.x + i * 0.4f + z + offset.y,
             p.x + i * 0.4f + z + offset.z, 0.0f);
    o += (add_val.cos() + 1.0f) / d;
  }

  // final output: o = tanh(o*o / 4e2)
  o = (o * o / 400.0f).tanh();

  return o;
}