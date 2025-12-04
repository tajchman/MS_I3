#include <iostream>

#include "arguments.hxx"
#include "timer.hxx"
#include "matrix.hxx"
#include "multiplier.hxx"
#include <tbb/parallel_for.h>
#include <tbb/task_arena.h>

int main(int argc, char **argv)
{
  Arguments Args(argc, argv);

  int n = Args.Get("n", 10000);
  int nThreads = Args.Get("threads", 1);

  tbb::task_arena arena(nThreads);
  Timer T;

  std::cout << "Memory allocation :    ";
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
  tbb::blocked_range2d<int> r(0, n, 0, n);
  arena.execute([&]{tbb::parallel_for(r, Mul);});

  T.stop();
  std::cout << T.elapsed() << " s" << std::endl;
   
  std::cout << " C(" << n/2 << ", " << n/2 << ") : " << C(n/2, n/2)
            << std::endl;
}
