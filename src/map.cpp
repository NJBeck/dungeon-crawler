#include "map.h"

_map::_map() {
    fill = .5;
    for (auto &arr : map_){
        arr.fill(false);
    }
}

_map::_map(double& fill_factor): fill(fill_factor) {
    for (auto &arr : map_){
        arr.fill(false);
    }
}

void _map::generatemap(std::vector<std::array<int, 2>> heads) {
    std::vector<std::array<int, 2>> temp_heads;
    std::uniform_real_distribution<double> distribution(0.0, 1.0);
    int n = map_.size();
    if (heads.size() == 0) {
        if (map_[n / 2][n / 2] != true) {

            // 5 central orthogonal spaces are available by default
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
                if (!map_[i][j] && (fill > generator.uniform_unit_double())) {
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

//void _map::populate_map(){
//    for (unsigned long long i = 0; i < map_.size(); ++i){
//        for (unsigned long long j = 0; j < map_[i].size(); ++j){
//            if (map_[i][j] && (encounter_rate > generator.uniform_unit_double()))
//            {
//                characters[i][j].emplace_back();
//            }
//        }
//    }
//}
