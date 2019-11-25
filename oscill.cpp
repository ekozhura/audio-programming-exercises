#include <cmath>
#include <cstdio>

struct Osc {
  double amp;
  double fr;
  const double *table;
  unsigned int size;
  double ph;
  double *s;
  unsigned int vsize;
  double sr;

  Osc (double a, double f, const double *t,
      unsigned int sz, double phs = 0.,
      unsigned int vsz = 64,
      double esr = 44100.
    ) : amp(a), fr(f), table(t), size(sz), ph(phs), 
        s(new double[vsz]), vsize(vsz), sr(esr) { };

  ~Osc() { delete[] s; }

  const double *process (double a, double f) {
    double incr = size * f / sr;
    amp = a; fr = f;
    for (int i = 0; i < vsize; i++) {
      s[i] = amp * table[(int) ph];
      ph += incr;
      while(ph >= size) ph -= size;
      while(ph < 0) ph += size;
    }
    return s;
  }

  const double *process(double a) {
    amp = a;
    return process(amp, fr);
  }

  const double *process() {
    return process(amp, fr);
  }
};