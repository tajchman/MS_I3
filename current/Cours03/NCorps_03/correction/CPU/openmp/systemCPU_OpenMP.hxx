#pragma once

#include "systemCPU.hxx"

class SystemCPU_OpenMP: public SystemCPU
{
  public:

    SystemCPU_OpenMP(Parameters & P);

  protected:
    void applyForces(REAL dT);
    void updatePositions(REAL dT);

};
