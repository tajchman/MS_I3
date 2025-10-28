#include "init.h"
#include "calcul.h"
#include <stdio.h>
#include <stdlib.h>
#include "timer.h"

int main(int argc, char **argv) {

  int n = argc > 1 ? strtol(argv[1], NULL, 10) : 10000000;
  Timer T1, T2;

  double *x, *y, a, b;
  x = init(n, 1.0);
  y = init(n, 0.0);
  a = 3.0;
  b = 4.0;

  TimerStart(&T1);
      
  calcul1(y, a, x, b, n);
    
  TimerStop(&T1);

  TimerStart(&T2);
      
  calcul2(y, a, x, b, n);
    
  TimerStop(&T2);

  printf("          temps cpu\n");
  printf("calcul1 (boucle simple) : %g s\n", T1.elapsed);
  printf("calcul2  (paquets de 4) : %g s\n", T2.elapsed);

  free(x);
  free(y);
  return 0;
 }
