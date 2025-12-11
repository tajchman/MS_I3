#pragma once

#include "system.hxx"

class SystemCPU_THREADS : public System
{
  public:

    SystemCPU_THREADS(Parameters & P) : System(P, "std::threads") {}

  protected:
    void applyForces(REAL dT);
    void updatePositions(REAL dT);

};
