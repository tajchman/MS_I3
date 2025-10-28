#include <iostream>
#include <vector>
#include <cmath>

#include "timer.hxx"
#include "arguments.hxx"

int main(int argc, char **argv)
{
  std::cout << "Utilisation d'un tableau double *" << std::endl;

  Arguments Args(argc, argv);
  size_t n = Args.Get("n", 1000000000L);
  size_t i;

  Timer T1a("alloue");
  T1a.start();
  double *v = new double[n];
  T1a.stop();
  std::cout << T1a << std::endl;
  
  Timer T1b("init");
  T1b.start();
  for (i=0; i<n; i++)
    v[i] = 0.0;
  T1b.stop();
  std::cout << T1b << std::endl;

  Timer T2("calcul");
  for (i=0; i<n; i++)
    v[i] = i*0.001;
  T2.stop();
  std::cout << T2 << std::endl;
 
  delete[] v;

  return 0;
}