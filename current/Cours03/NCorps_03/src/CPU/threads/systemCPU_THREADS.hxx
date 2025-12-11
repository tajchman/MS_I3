#pragma once

#include "systemCPU.hxx"

class SystemCPU_THREADS : public SystemCPU
{
  public:

    SystemCPU_THREADS(Parameters & P) : SystemCPU(P, "THREADS") {}

  protected:
    void applyForces(REAL dT);
    void updatePositions(REAL dT);

};
