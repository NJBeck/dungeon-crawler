#pragma once

#include <vector>
#include <iostream>
#include <array>
#include "rng.h"
#include "character.h"

class _map {
    /*
    map is a 2d array of bools representing cells which can be reached
    we start with a kernel just the center cell and the orthogonally adjacent ones for now
    but we can use any predefined shape for stitching maps together in the future

    for every 'true' space we check every surrounding cell
    if it isnt also true we compare a random seeded number from a [0, 1) uniform distribution
    to the "fill_factor". If fill_factor (default is .5 and seems to work well) is larger
    then that space also becomes true and is added
    to a new list of 'heads' which are used in the next round of filling out the map.
    This continues until there are no more heads to consider.
    */
public:
    std::array<std::array<bool, 128>, 128>  map_; //should change to bitfield to save space
    // every cell has a vector of characters
    std::array<std::array<std::vector<character>, 128>, 128> enemies;

    _map(double&);
    _map();
    void generatemap(std::vector<std::array<int, 2>> heads = {{}});
    void print_map(std::ostream&);
    //void populate_map();
private:
    double fill;
    //double encounter_rate; // odds of encountering an enemy on average
    rng generator;
};



