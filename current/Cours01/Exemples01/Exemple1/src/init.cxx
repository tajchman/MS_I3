#include "init.hxx"
#include <cstdlib>
#include <ctime>

void init(double *u, int n, int dn)
{
  size_t i;

  srand(time(NULL));

 for (i = 0; i<n; i++)
    u[i*dn] = 2.0 + rand();
}
