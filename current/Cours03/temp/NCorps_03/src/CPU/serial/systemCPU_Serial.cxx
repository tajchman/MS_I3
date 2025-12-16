#include "systemCPU_Serial.hxx"
#include <cmath>
#include <iostream>
#include <iomanip>

void SystemCPU_Serial::applyForces(REAL dT)
{
  REAL damping = _p.damping;
  REAL softeningSquared = _p.softening * _p.softening;
  REAL *p = pos(), *v = vel(), *m = mass(), *s = speed();

  for (int i = 0; i < _n; ++i)
  {
    REAL fx = 0.0, fy = 0.0, fz = 0.0;
    REAL x0 = p[3*i], y0 = p[3*i+1], z0 = p[3*i+2];

    for (int j = 0; j < _n; ++j)
    {
      REAL dx = p[3*j  ] - x0;
      REAL dy = p[3*j+1] - y0;
      REAL dz = p[3*j+2] - z0;
 
      REAL distSqr = dx * dx + dy * dy + dz * dz + softeningSquared;

      REAL s = _mass[i] / SQRT(distSqr * distSqr * distSqr);

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

void SystemCPU_Serial::updatePositions(REAL dT)
{
  REAL *p = pos(), *v = vel();
  for (int i = 0; i < 3*_n; ++i)
  {
    p[i] += v[i] * dT;
  }
}


