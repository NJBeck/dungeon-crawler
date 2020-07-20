#include "map.h"

_map::_map(): fill(.5) {}

_map::_map(double& fill_factor): fill(fill_factor) {}

void _map::generatemap(std::vector<std::array<int, 2>> heads) {
    std::vector<std::array<int, 2>> temp_heads;
    std::uniform_real_distribution<double> distribution(0.0, 1.0);
    int n = map.size();
    if (heads.size() == 0) {
        if (map[n / 2][n / 2] != true) {

            // 5 central orthogonal spaces are available by default
            map[n / 2][n / 2] = true;
            map[n / 2 + 1][n / 2] = true;
            map[n / 2 - 1][n / 2] = true;
            map[n / 2][n / 2 + 1] = true;
            map[n / 2][n / 2 - 1] = true;

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
                if (!map[i][j] && (fill > generator.uniform_unit_double())) {
                    map[i][j] = true;
                    temp_heads.push_back(nb);
                }
            }
        }
    }
    return _map::generatemap(temp_heads);
}

