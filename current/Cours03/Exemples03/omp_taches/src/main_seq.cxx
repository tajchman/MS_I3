#include "arguments.hxx"
#include "timer.hxx"
#include <iostream>

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

int main(int argc, char **argv)
{
  Timer T;

  Arguments A(argc, argv);
  int n = A.Get("n", 45);

  T.start();

  long f = fib_seq(n);

  T.stop();
  
  std::cerr << "fib(" << n << ") = " << f << std::endl;
  std::cerr << "CPU time : " << T.elapsed() << " s" 
            << std::endl;
}
