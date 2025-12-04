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

long fib_sections(int n, int lv)
{

  if (lv > level_max) return fib_seq(n);
    
  long i, j;
  if (n<2)
    return n;
  else {
    lv++;
    
    #pragma omp parallel sections shared(i,j,n, lv)
    {
      #pragma omp section
      i = fib_sections(n-1, lv);		
      #pragma omp section
      j = fib_sections(n-2, lv);		
    }
    return i + j;
  }
}

int main(int argc, char **argv)
{
  Timer T;

  Arguments A(argc, argv);
  int n = A.Get("n", 45);
  level_max = A.Get("levels", 4);

  //omp_set_nested(1);
  omp_set_max_active_levels(level_max);
  
  T.start();

  long f = fib_sections(n, 0);

  T.stop();

  std::cerr << "fib(" << n << ") = " << f << std::endl;
  std::cerr << "CPU time : " << T.elapsed() << " s" 
            << std::endl;
}

