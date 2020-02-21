#ifndef RNG_H
#define RNG_H

#include <random>
#include <time.h>
struct rng{
    std::mt19937 gen;
    unsigned long seed;
    std::uniform_real_distribution<double> uni_real_dist;

    rng();
    double uniform_unit_double();
};

#endif // RNG_H
