#pragma once

#include "systemCPU.hxx"
#include <tbb/task_arena.h>

class SystemCPU_TBB : public SystemCPU
{
  public:

    SystemCPU_TBB(Parameters & P);

  protected:
    void applyForces(REAL dT);
    void updatePositions(REAL dT);
    tbb::task_arena arena;

};
