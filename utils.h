#ifndef UTILS_H
#define UTILS_H

#include <sndfile.h>

SNDFILE *openSoundfile(char *filename, char openFileFlag, SF_INFO *info);
void process(double *inbuf, double *outbuf, sf_count_t cnt);
#endif