#include <math.h>
#include <stdio.h>

double B(int k)
{
    // Calcul
    const int n = 1000000;
    double x = 0.0;
    for (int i=0; i<n; i++)
       x = x + sin(k*3.1415*i/n);
    return x;
}

double A()
{
    double x = 0.0;

    for (int k=1; k<100; k++)
        x += B(k);

    const long m = 50000000;
    for (long i=0; i<m; i++)
       x += cos(3.1415*i/m);

    return x;
}


int main(int argc, char **argv)
{
    printf("resultat : %g\n", A());
    return 0;
}
