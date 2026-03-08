#include "include/mat2.h"
#include "include/perlin.h"
#include "include/vec2.h"
#include "include/vec4.h"
#include <math.h>
#include <stdio.h>

int main() {
  int frames = 60, frameRate = 60;
  char buf[256];
  for (int frame = 0; frame < frames; frame++) {
    snprintf(buf, sizeof(buf), "output-%02d.ppm", frame);
    const char *outputPath = buf;
    const int scale = 60;
    // .ppm starts as a text format then switch to binary format
    FILE *file = fopen(outputPath, "wb");
    int w = 16 * scale, h = 9 * scale;
    fprintf(file, "P6\n");
    fprintf(file, "%d %d\n", w, h);
    fprintf(file, "255\n");

    vec2 r = {(float)w, (float)h}; // screen res
    for (int y = 0; y < h; y++) {
      for (int x = 0; x < w; x++) {
        vec2 FC = {(float)x, (float)y};     // pixel coordinate
        vec4 o;                             // output
        float t = (float)frame / frameRate; // time

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
        vec2 p = vec2_divf(vec2_sub(FC, vec2_multf(r, 0.5f)), r.y);
        mat2 M = {8, -6, 6, 8};
        p = mat2_mult_vec2(M, p);
        vec2 v = {0.0f, 0.0f};
        float f = 3.0f + perlin2d(p.x + t * 7.0f, p.y, 0.1f, 4);

        for (float i = 0; i++ < 50.0f; i++) {
          vec4 tmp = {1, 2, 3, 1};
          vec4 tmp2 =
              vec4_addf(vec4_cos(vec4_sin(vec4_multf(tmp, sin(i)))), 1.0f);

          o += (cos(sin(i) * vec4(1, 2, 3, 1)) + 1.) * exp(sin(i * i + t)) /
               length(max(v, vec2(v.x * f * .02, v.y)));
        }

        v = p + cos(i * i + (t + p.x * .1) * .03 + i * vec2(11, 9)) * 5.;
        o = tanh(pow(vec4_divf(o, 1e2), vec4(1.5)));
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
