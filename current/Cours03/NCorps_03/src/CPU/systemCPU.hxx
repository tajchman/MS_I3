#ifndef __SYSTEMCPU__
#define __SYSTEMCPU__

#include "system.hxx"

class SystemCPU : public System
{
  public:

    ~SystemCPU()
    {
      Timer *T = getTimer(TimeDeallocate);
      if (T) T->start();

      delete [] _pos;
      delete [] _vel;
      delete [] _temp;
      if (T) T->stop();
    }

    REAL *pos() { return _pos; }
    REAL *vel() { return _vel; }
    REAL *temp() { return _temp; }
    
  protected:

    SystemCPU(Parameters & P, const char *v) : System(P, v) {

      _version = v;
      Timer *T =getTimer(TimeAllocate);
      if (T) T->start();

      _pos = new REAL[_p.nBodies * 4];
      _vel = new REAL[_p.nBodies * 4];
      _temp = new REAL[_p.nBodies];
      if (T) T->stop();
    }

    REAL *_pos, *_vel, *_temp;
};

#endif
