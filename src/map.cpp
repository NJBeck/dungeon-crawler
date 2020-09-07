#include "map.h"

using namespace std;

map::map(): fill(.5), map_size(128) {
    cells = vector<vector<bool>>(map_size, vector<bool>(map_size, false));
}

rng map::generator = rng();

void map::generatemap(std::vector<std::array<int, 2>> heads) {

    // the heads which will be recursively passed in the function parameters
    std::vector<std::array<int, 2>> temp_heads;

    int& n = map_size;
    if (heads.size() == 0) {
        if (cells[n / 2][n / 2] != true) {

            // 5 central orthogonal spaces are available by default
            cells[n / 2][n / 2] = true;
            cells[n / 2 + 1][n / 2] = true;
            cells[n / 2 - 1][n / 2] = true;
            cells[n / 2][n / 2 + 1] = true;
            cells[n / 2][n / 2 - 1] = true;

            heads.push_back({ n / 2 + 1, n / 2 });
            heads.push_back({ n / 2 - 1, n / 2 });
            heads.push_back({ n / 2, n / 2 + 1 });
            heads.push_back({ n / 2, n / 2 - 1 });
        }
        else {
            return;
        }
    }
    for (auto& head : heads) {
        // every cell has 4 neighbors to roll the die against
        vector<array<int, 2>> neighbors = {
            {head[0] + 1,head[1]},
            {head[0] - 1,head[1]},
            {head[0],head[1] + 1},
            {head[0],head[1] - 1}
        };
        // for every neighbor if it's not the end of the map
        // we compare random number between 0 and 1 to the fill factor
        // if fill is larger we flip the bit and add the cell to the list of heads to explore

        for (auto& nb : neighbors) {
            int i = nb[0];
            int j = nb[1];
            if (i != 0 && i != (n - 1) && j != 0 && j != (n - 1)) {
                if (!cells[i][j] && (fill > generator.uniform_unit_double())) {
                    cells[i][j] = true;
                    temp_heads.push_back(nb);
                }
            }
        }
    }
    return map::generatemap(temp_heads);
}

