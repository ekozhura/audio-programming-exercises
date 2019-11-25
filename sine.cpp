#include <iostream>
#include <stdio.h>
#include <math.h>

#define FREQ 440
#define SR 44100
#define DUR 2.0
#define TWOPI  6.283185307179586

int main() {
  int n;
  double pi2osr = TWOPI/SR;
  for(n = 0; n < DUR * SR; n++) {
    printf("%f\n", sin(FREQ*pi2osr*n));
  }
  return 0;
}