#pragma once

#include <vector>
#include <iostream>
#include <random>


class map {
public:
	std::vector<std::vector<bool>> _map;
	map(int& size, long& seed, double& fill_factor);
	map(int size);
	map();
	void generatemap(std::vector<std::vector<int>> heads = {});
	std::ostream& print_map(std::ostream&);
private:
	std::mt19937 gen;
	int sz;
	double fill;
	unsigned long sd;
};