#ifndef _MULTIPLIER
#define _MULTIPLIER

#include <vector>
#include <iostream>
#include <thread>
#include "matrix.hxx"

class Multiplier {

public:
  Multiplier(const Matrix & a, 
      const Matrix & b, 
            Matrix & c)
    :_a(a), _b(b), _c(c)
  {    
  }

  void operator()(int iStart, int iEnd) const {
    blocMult(_c, _a, _b, iStart, iEnd, 0, _a.m(), 0, _c.m());
  }

private:
  const Matrix & _a; 
  const Matrix & _b;
  Matrix & _c;
};

#endif
