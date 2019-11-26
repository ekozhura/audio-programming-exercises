#include <stdlib.h>
#include <string.h>
#include <sndfile.h>
#include <portaudio.h>
#include "utils.h"

#define BUFFRAMES 4096

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

void createStreamParams(
    PaStreamParameters *params,
    int device, 
    int channelsNum, 
    PaSampleFormat sampleFormat, 
    PaTime latency) {
  params->device = (PaDeviceIndex) device;
  params->channelCount = channelsNum;
  params->sampleFormat = sampleFormat;
  params->suggestedLatency = latency;
  params->hostApiSpecificStreamInfo = NULL;
}

int playSound(SNDFILE *fin) {
  PaError err;
  PaStreamParameters outparams;
  PaStream *handle = NULL;
  int i, chn = 2, buffsize, sr = 44100, dev;

  float *buf, out = 0.f;

  err = Pa_Initialize();
  if (err == paNoError) {
    dev = Pa_GetDefaultOutputDevice();
    buffsize = BUFFRAMES * chn;
    buf = (float *) malloc(sizeof(float) * buffsize);
    memset(buf, 0, sizeof(float) * buffsize);

    createStreamParams(&outparams, dev, chn, paFloat32, (BUFFRAMES/(double) sr));

    err = Pa_OpenStream(
      &handle, NULL, &outparams, 
      sr, buffsize, paNoFlag, 
      NULL, NULL
    );

    if (err == paNoError) {
      err = Pa_StartStream(handle);
      if (err == paNoError) {
        long cnt, i;
        do {
          cnt = sf_read_float(fin, buf, BUFFRAMES);
          if (cnt > 0) {
            err = (int) Pa_WriteStream(handle, buf, cnt/chn);
            if(err != paNoError) printf("write error: %s \n", Pa_GetErrorText(err));
          } else break;
        } while (cnt > 0);
        Pa_StopStream(handle);
      }
      Pa_CloseStream(handle);
    }
    free(buf);
    sf_close(fin);
    Pa_Terminate();
  }
  return 0;

}

