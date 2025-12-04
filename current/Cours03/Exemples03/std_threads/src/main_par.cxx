#include <iostream>
#include <thread>

#include "arguments.hxx"
#include "timer.hxx"
#include "matrix.hxx"
#include "multiplier.hxx"

int main(int argc, char **argv)
{
  Arguments Args(argc, argv);

  int n = Args.Get("n", 2000);
  int nThreads = Args.Get("threads", 1);

  Timer T;

  std::cout << "Memory allocation :     ";
  T.start();
  Matrix A(n, n), B(n, n), C(n, n);
  A = 1.0;
  B = 2.0;
  C = 0.0;
  T.stop();
  std::cout << T.elapsed() << " s" << std::endl;

  Multiplier Mul (A, B, C);

  std::cout << "Matrix multiplication :  ";
  T.start();

  int iThread;
  int dn = n/nThreads;

  std::vector<std::thread> threads;
  int i0, i1 = 0;
  for (iThread = 0; iThread<nThreads; iThread++)
  {
    i0 = i1;
    i1 = i0 + dn;
    if (iThread == nThreads-1)
      i1 = n;

    threads.push_back(std::thread(Mul, i0, i1));
  }

  for (auto & th : threads)
    th.join();

  T.stop();
  std::cout << T.elapsed() << " s" << std::endl;
   
  std::cout << " C(" << n/2 << ", " << n/2 << ") : " << C(n/2, n/2)
            << std::endl;
}
