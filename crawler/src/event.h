#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "map.h"
#include "character.h"

class event {
public:
	event();
	std::vector<std::string> situation;
	std::vector<std::string> options;
	std::string selected;

	std::istream& get_selection(std::istream&);
	void make_selection(std::istream&, character&, map&, std::ostream&);
	std::ostream& print_situation(std::ostream&);
	std::ostream& print_options(std::ostream&);
	void check_moves(character&, map&);
	void move_north(character&, map&);
	void move_south(character&, map&);
	void move_east(character&, map&);
	void move_west(character&, map&);
};