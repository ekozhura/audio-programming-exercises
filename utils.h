#ifndef UTILS_H
#define UTILS_H

#include <sndfile.h>
#include <portaudio.h>

SNDFILE *openSoundfile( char *filename, 
                        char openFileFlag, 
                        SF_INFO *info );

void process( double *inbuf, double *outbuf, sf_count_t cnt );

void createStreamParams( PaStreamParameters *params,
                      int device, 
                      int channelsNum, 
                      PaSampleFormat sampleFormat, 
                      PaTime latency );

int playSound( SNDFILE *fin );

#endif