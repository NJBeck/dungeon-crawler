#include "rng.h"

rng::rng(): uni_real_dist(0.0, 1.0){
    seed = time(0);
    gen = std::mt19937(seed);
}
double rng::uniform_unit_double(){
    return uni_real_dist(gen);
}
