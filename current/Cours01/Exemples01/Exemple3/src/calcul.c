#include "calcul.h"

void calcul1(double *u, double *v, double *w, 
             const double *a, const double *b, const double *c, const double *d, int n)  {
    int i;

    for (i=0; i<n; i++) {
      u[i] = 2*a[i] + 3*b[i];
    }
    for (i=0; i<n; i++) {
      v[i] = 3*a[i] + 2*b[i];
      w[i] = c[i] + d[i];
    }
}

void calcul2(double *u, double *v, double *w, 
             const double *a, const double *b, const double *c, const double *d, int n) {
    int i;

    for (i=0; i<n; i++) {
      u[i] = 2*a[i] + 3*b[i];
      v[i] = 3*a[i] + 2*b[i];
    }
    for (i=0; i<n; i++) {
      w[i] = c[i] + d[i];
    }

}

