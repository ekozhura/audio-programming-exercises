#include <sndfile.h> 
#include "utils.h"

SNDFILE *openSoundfile(
    char *filename,
    char openFileFlag, 
    SF_INFO *info
  ) {
  SNDFILE *f;
  int flag = openFileFlag == 'w' ? SFM_WRITE : SFM_READ;
  f = sf_open(filename, flag, info);
  return f;
}

void process(double *inbuf, double *outbuf, sf_count_t cnt) {
  float pan = 0.5;
  for (int i = 0, j = 0; i < cnt; i ++) {
    outbuf[i] = inbuf[i]  * pan;
  }
}