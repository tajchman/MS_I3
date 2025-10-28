#include <iostream>
#include <vector>
#include <cmath>

#include "timer.hxx"
#include "arguments.hxx"

int main(int argc, char **argv)
{
  std::cout << "Utilisation d'un tableau double *" << std::endl;
  Arguments Args(argc, argv);
  size_t i, n = Args.Get("n", 1000000000L);

  Timer T1a("alloue");
  T1a.start();
  double *v = new double[n];
  T1a.stop();
  std::cout << T1a << std::endl;

  double * p;
  
  Timer T1b("init");
  T1b.start();
  for (i=0, p=v; i<n; i++)
    *p++ = 0.0;
  T1b.stop();
  std::cout << T1b << std::endl;

  Timer T2("calcul");
  for (i=0, p=v; i<n; i++)
    *p++ = i*0.001;
  T2.stop();
  std::cout << T2 << std::endl;
  
  delete[] v;

  return 0;
}
