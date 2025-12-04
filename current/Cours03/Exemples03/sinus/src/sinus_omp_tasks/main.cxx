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
    int nTasks = prm.nTasks;

    set_terms(prm.iMax);
     
    std::cerr << "\nn       : " << n
	      << "\nthreads : " << nThreads
	      << "\ntasks   : " << nTasks
	      << "\n" << std::endl;

    std::vector<double> pos(n, 0), v1(n, 0), v2(n, 0);
   
    T_calcul.start();

    omp_set_num_threads(nThreads);

    int dn = n/nTasks;
    #pragma omp parallel
    {
      #pragma omp master
      {
        for (int i=0; i<nTasks-1; i++)
          #pragma omp task firstprivate(i) 
          {          
            int n_start = i * dn;
            int n_end = (i+1) * dn;
            calcul(pos, v1, v2, n_start, n_end);
	    
            // #pragma omp critical
            // std::cerr << omp_get_thread_num() 
            //           << ": n1 = " << n_start 
            //           << " n2 = " << n_end << std::endl;
          }

        #pragma omp task
        {
          int n_start = (nTasks-1)*dn;
          int n_end = n;
          calcul(pos, v1, v2, n_start, n_end);
        }
      }
    }
    #pragma omp taskwait

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
      save("sinus_omp_tasks", pos, v1, v2);

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
