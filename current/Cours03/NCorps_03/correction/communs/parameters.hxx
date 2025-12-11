#ifndef _PARAMETERS_HXX
#define _PARAMETERS_HXX

#include <string>
#include "type.hxx"
#include "timer.hxx"

struct Parameters
{
  Parameters(int argc, char **argv);

  REAL timeStep;
  int nBodies;
  int nIterations;
#ifdef USE_GRAPHICS
  bool graphics;
#endif
  std::string initFile, outFile;
  int nThreads;
  REAL softening;
  REAL damping;
  bool output;

  int p_argc;
  char **p_argv;
};


#endif
