#include <vector>
#include <iostream>
#include <cstdlib>
#include <cmath>

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

    set_terms(prm.iMax);
     
    std::cerr << "\nn       : " << n
	      << "\n" << std::endl;

    std::vector<double> pos(n, 0), v1(n, 0), v2(n, 0);
   
    T_calcul.start();

    calcul(pos, v1, v2, 0, n);

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
      save("sinus_seq", pos, v1, v2);

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
