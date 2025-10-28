#include <iostream>

#include "matrix_bloc.hxx"
#include "timer.hxx"
#include "arguments.hxx"

void init(MatrixBloc &A, int i0=0, int j0=0)
{
    for (int i=0; i<A.n(); i++)
        for (int j=0; j<A.m(); j++) {
            A(i,j) = 1./(i - i0 + j - j0 + 1);
        }
}

int main(int argc, char **argv)
{
    Arguments Arg(argc, argv);
    int n = Arg.Get("n", 1000);
    int b = Arg.Get("b", n/100);

    std::cout << "multiplication de matrice " << n << " x " << n 
              << " par bloc de " << b << " x " << b << std::endl;
    MatrixBloc A, B, C;
    A.resize(n, n, b, b);
    B.resize(n, n, b, b);
    C.resize(n, n, b, b);
    init(A);
    init(B);
    C = 0.0;

    if (n <= 10) {
        std::cout << "A" << A << std::endl;
        std::cout << "B" << B << std::endl;
    }
    Timer T;

    matMult(C, A, B);

    std::cout << T << std::endl;

    if (n <= 10) {
        std::cout << "C" << C << std::endl;
    }

    std::cout << "C(" << n/2 << ", " << n/2 << ") = " << C(n/2,n/2) << std::endl;
    return 0;
}
