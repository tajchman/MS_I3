#include "arguments.hxx"
#include "timer.hxx"
#include "multiplier.hxx"
#include <iostream>

int main(int argc, char **argv)
{
  Arguments Args(argc, argv);

  int n = Args.Get("n", 10000);

  Timer T;

  std::cout << "Memory allocation :     ";
  T.start();
  Matrix A(n, n), B(n, n), C(n, n);
  A = 1.0;
  B = 2.0;
  C = 0.0;
  T.stop();
  std::cout << T.elapsed() << " s" << std::endl;

  std::cout << "Matrix multiplication : ";
  T.start();
    
  Multiplier Mul (A, B, C);

  tbb::blocked_range<int> r(0, n);
  Mul(r); 

  T.stop();
  std::cout << T.elapsed() << " s" << std::endl;
   
  std::cout << " C(" << n/2 << ", " << n/2 << ") : " << C(n/2, n/2)
            << std::endl;
}
