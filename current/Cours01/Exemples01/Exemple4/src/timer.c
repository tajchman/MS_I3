#include "timer.h"
#include <stdlib.h>

void TimerStart(Timer * T)
{
#ifdef WIN32
  QueryPerformanceFrequency(&T->frequency);
  QueryPerformanceCounter(&(T->t0));
#else
  timespec_get(&T->ts0, TIME_UTC);
#endif
}

void TimerStop(Timer *T) 
{
#ifdef WIN32
  LARGE_INTEGER t1;
  QueryPerformanceCounter(&t1);
  T->elapsed += (t1.QuadPart - T->t0.QuadPart) * 1000.0 / T->frequency.QuadPart;
#else
  struct timespec ts;
  timespec_get(&ts, TIME_UTC);
  T->elapsed += (ts.tv_sec - T->ts0.tv_sec) + 1e-9 * (ts.tv_nsec - T->ts0.tv_nsec);
#endif
}
