#include <iostream>
#include <vector>
#include <cmath>


#include "timer.hxx"
#include "arguments.hxx"

int main(int argc, char **argv)
{
  std::cout << "Utilisation d'un vecteur C++" << std::endl;
  Arguments Args(argc, argv);
  bool pause = Args.Get("pause", false);
  size_t i, n = Args.Get("n", 1000000000L);
  char c;

  std::cout << "Debut ";
  if(pause)
    std::cin >> c;

  Timer T1("alloue/init");
  std::vector<double> v(n);
  T1.stop();

  std::cout << "Fin alloue/init ";
  if(pause)
    std::cin >> c;

  Timer T2("calcul");
  for (i=0; i<n; i++)
    v[i] = i*0.001;
  T2.stop();
  
  std::cout << "Fin calcul ";

  std::cout << T1 << std::endl << T2 << std::endl;

  return 0;
}
