#include "init.h"
#include "calcul.h"
#include <stdio.h>
#include <stdlib.h>
#include "timer.h"

int main(int argc, char **argv) {

  int n = argc > 1 ? strtol(argv[1], NULL, 10) : 100000000;
  Timer T1, T2;

  double *u, *v, *w, *a, *b, *c, *d;
  u = init(n, 1.0);
  v = init(n, 2.0);
  a = init(n, 3.0);
  b = init(n, 4.0);
  c = init(n, 0.0);
  d = init(n, 0.0);
  w = init(n, 0.0);

  printf("                           temps cpu\n");
  TimerStart(&T1);
      
  calcul1(u, v, w, a, b, c, d, n);
    
  TimerStop(&T1);
  printf("'mauvaise' loc. temporelle %g s\n", T1.elapsed);

  TimerStart(&T2);
      
  calcul2(u, v, w, a, b, c, d, n);
    
  TimerStop(&T2);
  printf("   'bonne' loc. temporelle %g s\n", T2.elapsed);

  double diff = T1.elapsed - T2.elapsed;
  double rel = diff / T1.elapsed * 100;
  printf("\ndifference ('mauvaise loc' - 'bonne loc'): %g s (%g %%)\n\n", diff, rel);

  free(u);
  free(v);
  free(a);
  free(b);
  free(c);
  free(d);
  free(w);
  return 0;
 }
