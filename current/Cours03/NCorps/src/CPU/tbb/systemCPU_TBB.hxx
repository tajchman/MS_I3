#pragma once

#include "systemCPU.hxx"

class SystemCPU_TBB : public SystemCPU
{
  public:

    SystemCPU_TBB(Parameters & P) : SystemCPU(P, "TBB") {}

  protected:
    void applyForces(REAL dT);
    void updatePositions(REAL dT);

};
