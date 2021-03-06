#include <unistd.h>
#include <stdio.h>

#define BUF_SIZE 256
#define ZEROS 60

float gain = 7.423339364f;
static float v[ZEROS+1];
float coeffs[] =
{ -0.0083649323f, -0.0265444850f, -0.0428141462f, -0.0537571943f,
-0.0564141052f, -0.0489161045f, -0.0310068662f, -0.0043393881f,
+0.0275375106f, +0.0595423283f, +0.0857543325f, +0.1003565948f,
+0.0986944931f, +0.0782804830f, +0.0395670487f, -0.0136691535f,
-0.0744390415f, -0.1331834575f, -0.1788967208f, -0.2005995448f,
-0.1889627181f, -0.1378439993f, -0.0454976231f, +0.0847488694f,
+0.2444859269f, +0.4209222342f, +0.5982295474f, +0.7593684540f,
+0.8881539892f, +0.9712773915f, +0.9999999166f, +0.9712773915f,
+0.8881539892f, +0.7593684540f, +0.5982295474f, +0.4209222342f,
+0.2444859269f, +0.0847488694f, -0.0454976231f, -0.1378439993f,
-0.1889627181f, -0.2005995448f, -0.1788967208f, -0.1331834575f,
-0.0744390415f, -0.0136691535f, +0.0395670487f, +0.0782804830f,
+0.0986944931f, +0.1003565948f, +0.0857543325f, +0.0595423283f,
+0.0275375106f, -0.0043393881f, -0.0310068662f, -0.0489161045f,
-0.0564141052f, -0.0537571943f, -0.0428141462f, -0.0265444850f,
-0.0083649323f,
};


short rrc_filter(short sample)
{
  float sum; int i;
  
  for (i = 0; i < ZEROS; i++)
      v[i] = v[i+1];

  v[ZEROS] = sample; // unfiltered sample in
  sum = 0.0f;

  for (i = 0; i <= ZEROS; i++)
    sum += (coeffs[i] * v[i]);

  return (short)(sum / gain); // filtered sample out
}

short buf[BUF_SIZE];
int r = 0;

void main() {
    while ((r = fread(buf, 2, BUF_SIZE, stdin)) > 0) {
        int i;
        for (i = 0; i < r; i++) {
            buf[i] = rrc_filter(buf[i]);
        }
        fwrite(buf, 2, r, stdout);
    }
}
