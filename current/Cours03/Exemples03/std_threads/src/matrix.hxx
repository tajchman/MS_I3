#ifndef __MATRIX_HXX
#define __MATRIX_HXX

#include <iostream>

class Matrix {
    public:
        Matrix() : _n(0), _m(0), _data(nullptr) {}
        Matrix(int n, int m) : _n(n), _m(m), _data(new double[_n*_m]) {}
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

inline void blocMult(Matrix & c, const Matrix & a, const Matrix & b, 
                     int n1, int n2, int k1, int k2, int m1, int m2)
{
    int i, j, k, n = a.n(), m = b.n(), p = b.m();
    if (a.m() != m) throw -1;

    for (i=n1; i<n2; i++)
        for (j=m1; j<m2; j++) {
            double s = 0.0;
            for (k=k1; k<k2; k++)
                s += a(i,k) * b(k, j);
            c(i,j) = s;
        }
}

std::ostream & operator<<(std::ostream & f, const Matrix & m);

#endif
