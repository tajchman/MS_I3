#ifndef _MULTIPLIER
#define _MULTIPLIER

#include <vector>
#include <iostream>
#include <thread>
#include "matrix.hxx"
#include "tbb/blocked_range.h"

class Multiplier {

public:
  Multiplier(const Matrix & a, 
      const Matrix & b, 
            Matrix & c)
    :_a(a), _b(b), _c(c)
  {    
  }

  void operator()(tbb::blocked_range<int> r) const {
      for (int i = r.begin(); i != r.end(); ++i) {
        for (int j = 0; j < _c.m(); ++j) {
          for (int k = 0; k < _a.m(); ++k) {
                    _c(i,j) += _a(i,k) * _b(k,j);
                }
            }
        }
    }

private:
  const Matrix & _a; 
  const Matrix & _b;
  Matrix & _c;
};

#endif

