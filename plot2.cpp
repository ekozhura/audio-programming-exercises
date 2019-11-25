#include <stdio.h>
#include <math.h>

#define COLS 80
#define LINS 24

void plot(float *data, int ymin, int ymax, int nx) {
  int n, m;
  for(m = ymax; m >= ymin; m--) {
    for (n = 0; n < nx; n++) {
      if (m == 0) printf("-");
      else if (lround(data[n]*ymax) == m) 
        printf("*");
      else printf(" ");
    }
    printf("\n");
  }
}

int main() {
  float buffer[COLS];
  int err, n;

  do {
    for( n = 0; n < COLS; n++) {
      err = scanf("%f", &buffer[n]);
    }

    plot(buffer, -(LINS-1)/2, (LINS-1)/2, COLS);

    for(n = 0; n < COLS; n++) {
      buffer[n] = 0;
    }
  } while (err != EOF);
  return 0;
}