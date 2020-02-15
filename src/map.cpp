#include "map.h"



_map::_map(long& seed, double& fill_factor) : sd(seed), fill(fill_factor) {
    for (auto &arr : map_){
        arr.fill(false);
    }
    gen = std::mt19937(seed);
}

_map::_map() {
    sd = time(0);
    fill = .5;
    for (auto &arr : map_){
        arr.fill(false);
    }
    gen = std::mt19937(sd);
}

_map::_map(long& seed): sd(seed) {
    fill = .5;
    for (auto &arr : map_){
        arr.fill(false);
    }
    gen = std::mt19937(sd);
}

_map::_map(double& fill_factor): fill(fill_factor) {
    sd = time(0);
    for (auto &arr : map_){
        arr.fill(false);
    }
    gen = std::mt19937(sd);
}

void _map::generatemap(std::vector<std::array<int, 2>> heads) {
    std::vector<std::array<int, 2>> temp_heads;
    std::uniform_real_distribution<double> distribution(0.0, 1.0);
    int n = map_.size();
    if (heads.size() == 0) {
        if (map_[n / 2][n / 2] != true) {

            map_[n / 2][n / 2] = true;
            map_[n / 2 + 1][n / 2] = true;
            map_[n / 2 - 1][n / 2] = true;
            map_[n / 2][n / 2 + 1] = true;
            map_[n / 2][n / 2 - 1] = true;

            std::array<int, 2> temp{ n / 2 + 1, n / 2 };
            heads.push_back(temp);

            temp = { n / 2 - 1, n / 2 };
            heads.push_back(temp);

            temp = { n / 2, n / 2 + 1 };
            heads.push_back(temp);

            temp = { n / 2, n / 2 - 1 };
            heads.push_back(temp);
        }
        else {
            return;
        }
    }
    for (auto& head : heads) {
        std::vector<std::array<int, 2>> neighbors = { {head[0] + 1,head[1]},{head[0] - 1,head[1]},{head[0],head[1] + 1},{head[0],head[1] - 1} };
        for (auto& nb : neighbors) {
            int i = nb[0];
            int j = nb[1];
            if (i != 0 && i != (n - 1) && j != 0 && j != (n - 1)) {
                if (!map_[i][j] && (fill > distribution(gen))) {
                    map_[i][j] = true;
                    temp_heads.push_back(nb);
                }
            }
        }
    }
    return _map::generatemap(temp_heads);
}

void _map::print_map(std::ostream& outs) {
    for (auto& row : map_) {
        for (auto val : row) {
            if (val == true) {
                outs << "X ";
            }
            else {
                outs << "| ";
            }
        }
        outs << std::endl;
    }
}
