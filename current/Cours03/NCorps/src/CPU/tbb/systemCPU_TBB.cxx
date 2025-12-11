#include "systemCPU_TBB.hxx"
#include <cmath>
#include <iostream>
#include <iomanip>

#include <tbb/parallel_for.h>
#include <tbb/blocked_range.h>
 
static void threadApplyForces(int first, int last,
                              int n, const REAL * p, REAL *v, REAL *mass, REAL *s,
                              REAL softeningSquared, REAL damping, REAL dT)
{
  for (int i = first; i < last; ++i)
  {
    REAL fx = 0.0, fy = 0.0, fz = 0.0;
    REAL x0 = p[3*i], y0 = p[3*i+1], z0 = p[3*i+2];

    for (int j = 0; j < n; ++j)
    {
      REAL dx = p[3*j  ] - x0;
      REAL dy = p[3*j+1] - y0;
      REAL dz = p[3*j+2] - z0;
 
      REAL distSqr = dx * dx + dy * dy + dz * dz + softeningSquared;

      REAL s = mass[i] / SQRT(distSqr * distSqr * distSqr);

      fx += dx * s;
      fy += dy * s;
      fz += dz * s;
    }
    v[3*i]   = (v[3*i]   + dT * fx)*damping;
    v[3*i+1] = (v[3*i+1] + dT * fy)*damping;
    v[3*i+2] = (v[3*i+2] + dT * fz)*damping;
    s[i] = SQRT(v[3*i]*v[3*i] + v[3*i+1]*v[3*i+1] + v[3*i+2]*v[3*i+2]);
 }
}


void SystemCPU_TBB::applyForces(REAL dT)
{

  REAL softeningSquared = _p.softening * _p.softening;
  REAL damping = _p.damping;

   tbb::parallel_for(
        tbb::blocked_range<int>(0,_p.nBodies),  
        [&](tbb::blocked_range<int> r) {
          threadApplyForces(r.begin(), r.end(),
              _p.nBodies, pos(), vel(), mass(), speed(),
              softeningSquared, damping, dT);
        }
      );
}

void SystemCPU_TBB::updatePositions(REAL dT)
{
  REAL *p = pos(), *v = vel();
  for (int i = 0; i < 3*_n; ++i)
  {
    p[i] += v[i] * dT;
  }
}


