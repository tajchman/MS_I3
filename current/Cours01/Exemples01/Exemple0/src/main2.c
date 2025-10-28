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

void A()
{
    const int n = 100;
    double *x = NULL;

    for (int k=0; k<n; k++)
        x[k] = B(k);
}


int main(int argc, char **argv)
{
    A();
    return 0;
}
