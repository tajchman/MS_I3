#ifndef __MATRIX_HXX
#define __MATRIX_HXX

#include <iostream>

class Matrix {
    public:
        Matrix() : _n(0), _m(0), _data(nullptr) {}
        ~Matrix() { delete [] _data; }

        void resize(int n, int m);
        void operator=(double v);
        void operator=(const Matrix & m);
        void operator+=(const Matrix & m);

        int n() const { return _n; }
        int m() const { return _m; }

        double operator() (int i, int j) const { return _data[i + j*_n]; }
        double & operator() (int i, int j) { return _data[i + j*_n]; }

        double * data() { return _data; }
        const double * data() const { return _data; }
        
    private:
        int _n, _m;
        double *_data;
};

void matMult(Matrix & c, const Matrix & a, const Matrix & b);

std::ostream & operator<<(std::ostream & f, const Matrix & m);

#endif
