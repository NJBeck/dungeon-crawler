

#include "map.h"
#include <time.h>
using namespace std;


map::map(int& size, long& seed, double& fill_factor) : sz(size), sd(seed), fill(fill_factor) {
	_map = vector<vector<bool>>(sz, vector<bool>(sz, false));
	gen = mt19937(seed);
}
map::map(int size) {
	sz = size;
	sd = time(0);
	fill = .5;
	_map = vector<vector<bool>>(sz, vector<bool>(sz, false));
	gen = mt19937(sd);
}
map::map() {
	sz = 128;
	sd = time(0);
	fill = .5;
	_map = vector<vector<bool>>(sz, vector<bool>(sz, false));
	gen = mt19937(sd);
}
void map::generatemap(std::vector<std::vector<int>> heads) {
	vector<vector<int>> temp_heads = vector<vector<int>>(0, vector<int>(2));
	uniform_real_distribution<double> distribution(0.0, 1.0);
	if (heads.size() == 0) {
		if (_map[sz / 2][sz / 2] != true) {

			_map[sz / 2][sz / 2] = true;
			_map[sz / 2 + 1][sz / 2] = true;
			_map[sz / 2 - 1][sz / 2] = true;
			_map[sz / 2][sz / 2 + 1] = true;
			_map[sz / 2][sz / 2 - 1] = true;

			vector<int> temp{ sz / 2 + 1, sz / 2 };
			heads.push_back(temp);

			temp = { sz / 2 - 1, sz / 2 };
			heads.push_back(temp);

			temp = { sz / 2, sz / 2 + 1 };
			heads.push_back(temp);

			temp = { sz / 2, sz / 2 - 1 };
			heads.push_back(temp);
		}
		else {
			return;
		}
	}
	for (auto& head : heads) {
		vector<vector<int>> neighbors = { {head[0] + 1,head[1]},{head[0] - 1,head[1]},{head[0],head[1] + 1},{head[0],head[1] - 1} };
		for (auto& nb : neighbors) {
			int i = nb[0];
			int j = nb[1];
			if (i != 0 && i != (sz - 1) && j != 0 && j != (sz - 1)) {
				if (!_map[i][j] && (fill > distribution(gen))) {
					_map[i][j] = true;
					temp_heads.push_back(nb);
				}
			}
		}
	}
	return map::generatemap(temp_heads);
}
ostream& map::print_map(ostream& outs) {
	for (auto& row : _map) {
		for (auto val : row) {
			if (val == true) {
				outs << "X ";
			}
			else {
				outs << "| ";
			}
		}
		outs << endl;
	}
	return outs;
}

