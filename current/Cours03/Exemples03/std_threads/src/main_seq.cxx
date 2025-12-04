#include "arguments.hxx"
#include "timer.hxx"
#include "multiplier.hxx"
#include <iostream>

int main(int argc, char **argv)
{
  Arguments Args(argc, argv);

  int n = Args.Get("n", 2000);

  Timer T;
  T.start();

  std::cout << "Memory allocation :     ";
  T.start();
  Matrix A(n, n), B(n, n), C(n, n);
  A = 1.0;
  B = 2.0;
  C = 0.0;
  T.stop();
  std::cout << T.elapsed() << " s" << std::endl;

  Multiplier Mul (A, B, C);

  std::cout << "Matrix multiplication : ";
  T.start();
    
  Mul(0, n); 

  T.stop();
  std::cout << T.elapsed() << " s" << std::endl;
   
  std::cout << " C(" << n/2 << ", " << n/2 << ") : " << C(n/2, n/2)
            << std::endl;
}
