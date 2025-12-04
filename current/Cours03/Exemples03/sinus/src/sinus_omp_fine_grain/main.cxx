#include <vector>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <omp.h>

#include "calcul.hxx"
#include "stat.hxx"
#include "sin.hxx"
#include "save.hxx"
#include "timer.hxx"
#include "parameters.hxx"

int main(int argc, char **argv)
{
  Timer T_total, T_calcul, T_stat, T_save;
  T_total.start();
  
  {
    Parameters prm(argc, argv);
    size_t n = prm.n;
    int nThreads = prm.nThreads;
    int chunkSize = prm.chunkSize;

    set_terms(prm.iMax);
     
    std::cerr << "\nn       : " << n
	      << "\nthreads : " << nThreads;

    if (chunkSize > 0)
	      std::cerr << "\nchunk   : " << chunkSize;
	  std::cerr << "\n" << std::endl;

    std::vector<double> pos(n, 0), v1(n, 0), v2(n, 0);
   
    T_calcul.start();

    omp_set_num_threads(nThreads);

    calcul(pos, v1, v2, 0, n, chunkSize);

    T_calcul.stop();
    T_stat.start();

    double m, e;
  
    stat(v1, v2, 0, n, m, e);

    m = m/n;
    e = sqrt(e/n - m*m);
    std::cerr << "m = " << m << " e = " << e << std::endl << std::endl;

    T_stat.stop();
    T_save.start();

    if (n <= 1000)
      save("sinus_fine_grain", pos, v1, v2);

    T_save.stop();
  }
  T_total.stop();
  std::cerr << "temps calcul : " << T_calcul.elapsed() << " s" << std::endl;
  std::cerr << "temps stat   : " << T_stat.elapsed() << " s" << std::endl;
  std::cerr << "temps save   : " << T_save.elapsed() << " s" << std::endl;
  std::cerr << std::endl;
  std::cerr << "temps total  : " << T_total.elapsed() << " s" << std::endl;
  return 0;
}
