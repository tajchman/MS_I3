#ifndef __URAND__
#define __URAND__

#include <random>

REAL urand() {
    static thread_local std::random_device rd;
    static thread_local std::mt19937 generator;
    std::uniform_real_distribution<REAL> distribution(0.0, 1.0);
    return distribution(generator);
}


#endif