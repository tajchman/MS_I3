#include "matrix_bloc.hxx"
#include <iostream>

void MatrixBloc::resize(int n, int m, int bn, int bm) {
    if (_data)
        delete [] _data;
    _n = n; _m = m;
    _bn = bn; _bm = bm;
    _nb = n/bn; _mb = m/bm;
    _data = new Matrix[_nb*_mb];

    for (int i=0; i<_nb*_mb; i++)
        _data[i].resize(_bn, _bm);
}

#include <iomanip>
std::ostream & operator<<(std::ostream & f, const MatrixBloc & m)
{
    f << std::endl;
    for (int i=0; i<m.n(); i++)
    {
        f << std::setw(3) << i;
        for (int j=0; j<m.m(); j++)
            f << std::setw(12) << m(i,j);
        f << std::endl;
    }
    return f;
}

void MatrixBloc::operator=(double v)
{
    int i, imax = _nb*_mb;
    for (i=0; i<imax; i++)
        _data[i] = v;
}

void matMult(MatrixBloc & c, const MatrixBloc & a, const MatrixBloc & b)
{
    int i, j, k, n = a.nb(), m = b.nb(), p = b.mb();
    if (a.mb() != m) throw -1;

    Matrix s, t;
    s.resize(a.bn(), a.bm());
    t.resize(a.bn(), a.bm());

    for (i=0; i<n; i++)
        for (j=0; j<p; j++) {
            s = 0.0;
            for (k=0; k<m; k++) {
                matMult(t, a.bloc(i,k), b.bloc(k,j));
                s += t;
            }
            c.bloc(i,j) = s;
        }
}

void MatrixBloc::operator+=(const MatrixBloc & a)
{
    int i, nm = _n * _m;
    Matrix * c_b = _data;
    const Matrix * c_a = a.data();
    for (i=0; i<nm; i++, c_b++, c_a++)
        *c_b += *c_a;
}
