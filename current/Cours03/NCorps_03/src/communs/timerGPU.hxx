#ifndef __TIMERGPU__
#define __TIMERGPU__

#include "timer.hxx"
#include <cuda_runtime.h>

class TimerGPU : public Timer
{
  public:

    TimerGPU(const char *s = "", int o = 0) : Timer(s, o) {
      cudaEventCreate(&_start);
      cudaEventCreate(&_stop);
    }
    
    void start() {
      cudaEventRecord( _start, 0 );
    }

    void stop() {
      float elapsed_time;
      cudaEventRecord(_stop, 0);
      cudaEventSynchronize(_stop);
    
      cudaEventElapsedTime(&elapsed_time, _start, _stop);
      _elapsed += 1e-3 * elapsed_time;

    }

  protected:
  
    cudaEvent_t _start, _stop;
};


#endif