#include "matrix.hxx"

void Matrix::operator=(double v)
{
    int i, imax = _n*_m;
    for (i=0; i<imax; i++)
        _data[i] = v;
}

void Matrix::operator= (const Matrix & m)
{
    int i, imax = _n*_m;
    const double * _cm = m.data();

    for (i=0; i<imax; i++)
        _data[i] = _cm[i];
}

void Matrix::resize(int n, int m) {
    if (_data)
        delete [] _data;
    _data = new double[n*m];
    _n = n;
    _m = m;
}

#include <iomanip>
std::ostream & operator<<(std::ostream & f, const Matrix & m)
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


void Matrix::operator+=(const Matrix & a)
{
    int i, nm = _n * _m;
    const double * c_a = a.data();
    for (i=0; i<nm; i++)
        _data[i] += c_a[i];
}
