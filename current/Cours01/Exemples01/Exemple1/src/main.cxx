#include "init.hxx"
#include "calcul.hxx"
#include "arguments.hxx"
#include "timer.hxx"

#include <stdlib.h>

int main(int argc, char **argv) {

  Arguments Arg(argc, argv);
  int n = Arg.Get("n", 10);
  int d = Arg.Get("d", 1);

  double *u = new double[(n+2)*d];
  double *v = new double[(n+2)*d]; 

  init(u, n+2, d);

  calcul(v, u, n+2, d);

  delete [] v;
  delete [] u;
  return 0;
 }
