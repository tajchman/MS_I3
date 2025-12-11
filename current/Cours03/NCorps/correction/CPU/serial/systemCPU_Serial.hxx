#pragma once

#include "systemCPU.hxx"

class SystemCPU_Serial : public SystemCPU
{
  public:

    SystemCPU_Serial(Parameters & P) : SystemCPU(P, "Serial") {}

  protected:
    void applyForces(REAL dT);
    void updatePositions(REAL dT);

};
