#include <iostream>
#include <cstdlib>
#include <sndfile.h>
#include "oscill.cpp"
#include "utils.h"

using namespace std;

const double twopi = 8. * atan(1.);

int saveFile() {

  const int bframes = 512;
  double *inbuf, *outbuf;
  SNDFILE *fin, * fout;
  SF_INFO info_in, info_out;

  if ((fin = openSoundfile((char *) "unprocessed.wav", 'r', &info_in)) != NULL) {
      info_out.format = info_in.format;
      info_out.samplerate = info_in.samplerate;
      info_out.channels = 2;

      if ((fout = openSoundfile((char *) "processed.wav", 'w', &info_out)) != NULL) {
        size_t cnt;
        inbuf = (double *) calloc(bframes, sizeof(double));
        outbuf = (double *) calloc(bframes, sizeof(double));
        do {
          cnt = sf_read_double(fin, inbuf, bframes);
          process(inbuf, outbuf, cnt);
          sf_write_double(fout, outbuf, cnt);
        } while (cnt > 0);
        free(inbuf);
        free(outbuf);
        sf_close(fin);
        sf_close(fout);
      } else {
        sf_close(fin);
        return 1;
      }
  } else {
    return 1;
  }
  return 0;
}

int main() { 
  // const unsigned int size = 10000;
  // double tab[size];
  // const double *out;

  // Osc osc(0.5, 440., tab, size);

  // for(int i = 0; i < size; i++) {
  //   tab[i] = 05 * (sin(i*twopi/size) + sin(2*i*twopi/size));
  // }

  saveFile();
  SNDFILE *fin;
  SF_INFO info_in;
  fin = openSoundfile((char *) "unprocessed.wav", 'r', &info_in);
  
  playSound(fin);
  // for (int i = 0; i < osc.sr; i += osc.vsize) {
  //   out = osc.process();
  //   for (int j = 0; j < osc.vsize; j++) 
  //     printf("%f ", out[j]);
  // }
  return 0;
}