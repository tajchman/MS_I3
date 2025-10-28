#ifndef __MATRIX_BLOC_HXX
#define __MATRIX_BLOC_HXX

#include "matrix.hxx"
#include <iostream>

class MatrixBloc {
    public:
        MatrixBloc() : _n(0), _m(0), _nb(0), _mb(0), _bn(0), _bm(0), _data(nullptr) {}
        ~MatrixBloc() { delete [] _data; }

        void resize(int n, int m, int bn, int bm);
        void operator=(double v);

        int n() const { return _n; }
        int m() const { return _m; }
        int bn() const { return _bn; }
        int bm() const { return _bm; }
        int nb() const { return _nb; }
        int mb() const { return _mb; }

        double & operator() (int i, int j) {
            int ib = i/_bn;
            int jb = j/_bm;
            return bloc(ib, jb)(i-ib*_bn, j-jb*_bm); 
        }
        double  operator() (int i, int j) const { 
            int ib = i/_bn;
            int jb = j/_bm;
            return bloc(ib, jb)(i-ib*_bn, j-jb*_bm); 
        }
        
        Matrix & bloc(int i, int j) { return _data[i + j*_nb]; }
        const Matrix & bloc(int i, int j) const { return _data[i + j*_nb]; }
        void operator= (const MatrixBloc & m);
        void operator+=(const MatrixBloc & a);
        
        Matrix * data() { return _data; }
        const Matrix * data() const { return _data; }

    private:
        int _n, _m;
        int _nb, _mb;
        int _bn, _bm;
        Matrix *_data;
};

void matMult(MatrixBloc & c, const MatrixBloc & a, const MatrixBloc & b);

std::ostream & operator<<(std::ostream & f, const MatrixBloc & m);

#endif
