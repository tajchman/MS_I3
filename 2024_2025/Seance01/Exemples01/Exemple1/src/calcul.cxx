#include "calcul.hxx"
#include "timer.hxx"
#include <fstream>

void calcul(double *v, const double * u, int n, int dn)
{
  size_t i;
  
  std::ofstream f("results.dat");


  Timer T("calcul");
  v[0] = u[0];
  for (i = 1; i<n-1; i++) {
    
    T.reset();

    v[i] = (u[(i-1)*dn]+2.0*u[i*dn]+u[(i+1)*dn])/4;

    T.stop();
    f << i << " " << T.elapsed() << std::endl;
  }

  v[n-1] = u[n-1];
}
