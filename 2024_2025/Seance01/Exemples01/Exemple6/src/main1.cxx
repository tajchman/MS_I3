#include <iostream>
#include <vector>
#include <cmath>


#include "timer.hxx"
#include "arguments.hxx"

int main(int argc, char **argv)
{
  std::cout << "Utilisation d'un vecteur C++" << std::endl;

  Arguments Args(argc, argv);
  size_t i, n = Args.Get("n", 1000000000L);

  Timer T1("alloue");
  std::vector<double> v(n);
  T1.stop();

  Timer T2("init");
  for (i=0; i<n; i++)
    v[i] = 0.0;
  T2.stop();

  Timer T3("calcul");
  for (i=0; i<n; i++)
    v[i] = i*0.001;
  T3.stop();

  std::cout << T1 << std::endl << T2 << std::endl << T3 << std::endl;

  return 0;
}
