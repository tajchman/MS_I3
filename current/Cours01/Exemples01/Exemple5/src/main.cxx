#include <iostream>

#include "matrix.hxx"
#include "timer.hxx"
#include "arguments.hxx"

void init(Matrix &A, int i0=0, int j0=0)
{
    for (int i=0; i<A.n(); i++)
        for (int j=0; j<A.m(); j++)
            A(i,j) = 1./(i - i0 + j - j0 + 1);
}

int main(int argc, char **argv)
{
    Arguments Arg(argc, argv);
    int n = Arg.Get("n", 1000);

    std::cout << "multiplication de matrice " << n << " x " << n << std::endl;
    Matrix A, B, C;
    A.resize(n, n);
    B.resize(n, n);
    C.resize(n, n);
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
