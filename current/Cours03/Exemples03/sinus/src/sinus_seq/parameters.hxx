#ifndef _PARAMETERS_HXX
#define _PARAMETERS_HXX

#include <string>
#include "timer.hxx"

struct Parameters
{
  Parameters(int argc, char **argv);

  int n;
  int iMax;

  int p_argc;
  char **p_argv;
};


#endif
