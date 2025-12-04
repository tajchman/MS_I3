#include <cmath>
#include "calcul.hxx"
#include "sin.hxx"
#include "tbb/tbb.h"

struct sCalcul
{
  sCalcul(std::vector<double> & pos,
          std::vector<double> & v1,
          std::vector<double> & v2) : _pos(pos), _v1(v1), _v2(v2) {} 
          
  void operator() (const tbb::blocked_range<size_t>& r) const {
    double x;
    int i, n = _pos.size();

    for(size_t i = r.begin(); i != r.end(); i++) {
      x = i*2*M_PI/n;
      _pos[i] = x;
      _v1[i] = sinus_machine(x);
      _v2[i] = sinus_taylor(x);
    }
  }

  std::vector<double> & _pos, & _v1, & _v2;
};

void calcul(std::vector<double> & pos,
            std::vector<double> & v1,
            std::vector<double> & v2,
            int n1, int n2)
{
    tbb::parallel_for(tbb::blocked_range<size_t>(n1, n2), sCalcul(pos, v1, v2));
}
