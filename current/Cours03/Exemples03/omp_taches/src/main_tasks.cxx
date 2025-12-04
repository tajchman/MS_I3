#include "arguments.hxx"
#include "timer.hxx"
#include <iostream>
#include <iomanip>
#include <omp.h>

int level_max;

long fib_seq(int n)
{
  long i, j;
  if (n<2)
    return n;
  else
    {
       i=fib_seq(n-1);
       j=fib_seq(n-2);

       return i+j;
    }
}

long fib_tasks(int n, int lv)
{

  if (lv > level_max) return fib_seq(n);
    
  long i, j;
  if (n<2)
    return n;
  else {
    lv++;
#pragma omp task shared(i, n, lv)
    i=fib_tasks(n-1, lv);

#pragma omp task shared(j, n, lv)
    j=fib_tasks(n-2, lv);

#pragma omp taskwait

    return i + j;
  }
}

int main(int argc, char **argv)
{
  Timer T;
  T.start();

  Arguments A(argc, argv);
  int n = A.Get("n", 45);
  level_max = A.Get("levels", 3);
  int nthreads = A.Get("threads", 8);
  omp_set_num_threads(nthreads);

#pragma omp parallel
  {
#pragma omp single
    {
    long f = fib_tasks(n, 0);
    std::cerr << "fib(" << n << ") = " << f << std::endl;
    }
  }

  T.stop();
  std::cerr << "CPU time : " << T.elapsed() << " s" 
            << std::endl;
}

