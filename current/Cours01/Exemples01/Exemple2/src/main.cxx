#include "init.hxx"
#include "calcul.hxx"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include "timer.hxx"
#include "arguments.hxx"

int main(int argc, char **argv) {

  Arguments Args(argc, argv);
  int n = Args.Get("n", 1024);

  Matrice A(n,n), B(n,n), C(n,n);

  init(A, 1);
  init(B, 2);
  init(C, 0);

  std::cout << "                           temps cpu" << std::endl;

  Timer T1("Algo suivant les lignes   ");
      
  calcul1(C, A, B);
    
  std::cout << T1 << std::endl;

  Timer T2("Algo suivant les colonnes ");
      
  calcul2(C, A, B);
    
  std::cout << T2 << std::endl;

  return 0;
 }
