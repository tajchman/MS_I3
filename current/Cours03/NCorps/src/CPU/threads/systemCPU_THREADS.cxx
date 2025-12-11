#include "systemCPU_THREADS.hxx"
#include <cmath>
#include <thread>
#include <vector>
#include <iostream>
#include <iomanip>

static void threadApplyForces(int first, int last, int n,
                              const REAL * p, REAL *v, REAL *mass, REAL *s,
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

void SystemCPU_THREADS::applyForces(REAL dT)
{
  std::vector<std::thread> threads;

  REAL softeningSquared = _p.softening;
  REAL damping = _p.damping;

  for (int iTh = 0; iTh < _p.nThreads; iTh++)
  {
    int first, last, di;
    di = _n/_p.nThreads;
    first = iTh * di;
    last = (iTh < _p.nThreads-1) ? first + di : _n;

    threads.emplace_back(threadApplyForces, first, last, 
      _n, _pos, _vel, _mass, _speed,
      softeningSquared , damping, dT);
  }

  for (auto & th : threads)
    th.join();
}

void SystemCPU_THREADS::updatePositions(REAL dT)
{
  REAL *p = pos(), *v = vel();
  for (int i = 0; i < 3*_n; ++i)
  {
    p[i] += v[i] * dT;
  }
}


