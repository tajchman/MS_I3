#include "init.h"
#include <stdlib.h>

double * init(int n, double v0)
{
  int i;
  double *v = (double *) malloc(sizeof(double) * n);
  
  for (i=0; i<n; i++)
      v[i] = v0;

  return v;
}
