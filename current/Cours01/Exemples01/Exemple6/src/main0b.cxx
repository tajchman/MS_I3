#include <iostream>
#include <vector>
#include <cmath>

#include "timer.hxx"
#include "arguments.hxx"

int main(int argc, char **argv)
{
  Arguments Args(argc, argv);
  bool pause = Args.Get("pause", false);
  size_t i, n = Args.Get("n", 1000000000L);

  std::cout << "Utilisation d'un tableau double *" << std::endl;

  char c;

  std::cout << "Debut ";
  if(pause)
    std::cin >> c;
  
  Timer T1a("alloue");
  T1a.start();
  double *v = new double[n];
  T1a.stop();
  std::cout << T1a << std::endl;
  
 
  std::cout << "Fin allocation ";
  if(pause)
    std::cin >> c;

  Timer T1b("init");
  T1b.start();
  for (i=0; i<n; i++)
    v[i] = 0.0;
  T1b.stop();

  std::cout << "Fin initialisation ";
  if(pause)
    std::cin >> c;

  Timer T2("calcul");
  for (i=0; i<n; i++)
    v[i] = i*0.001;
  T2.stop();
  std::cout << T2 << std::endl;
  std::cout << "Fin calcul ";
 
  delete [] v;

  return 0;
}
