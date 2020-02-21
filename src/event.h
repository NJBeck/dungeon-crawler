#pragma once
#include <string>
#include "character.h"
#include "map.h"
#include <functional>
#include <unordered_map>
#include "rng.h"

class event {
public:
	event();
    /*
     * class that handles all the actions and events taken
     * at every loop the situation is printed at the top of the screen
     * and options are printed at the bottom
     * a selection is taken and matched to a hash map of associated functions
    */
	std::vector<std::string> situation;
	std::vector<std::string> options;
	std::string selected;

	std::istream& get_selection(std::istream&);
    void make_selection(std::istream&, character&, _map&, std::ostream&);
	std::ostream& print_situation(std::ostream&);
	std::ostream& print_options(std::ostream&);
    void check_moves(character&, _map&);
    void roll_encounter(character&, _map&, double encounter_rate = .5);
    void combat(character&, std::vector<character>&, _map&);
    void event_loop(std::ostream&, std::istream&, character&, _map&);

    // the actions available to characters
    void move_north(std::ostream&, std::istream&, character&, _map&);
    void move_south(std::ostream&, std::istream&, character&, _map&);
    void move_east(std::ostream&, std::istream&, character&, _map&);
    void move_west(std::ostream&, std::istream&, character&, _map&);
    void character_screen(std::ostream&, std::istream&, character&, _map&);
    // void exit(std::ostream&, std::istream&, character&, _map&);
    void back(std::ostream&, std::istream&, character&, _map&);
    void print_map(std::ostream&, std::istream&, character&, _map&);
    void print_inventory(std::ostream&, std::istream&, character&, _map&);

    // the hashmap of strings to actions
    typedef std::function<void(event&, std::ostream&, std::istream&, character&, _map&)> act;
    std::unordered_map<std::string, act> actions;
    act _north = &event::move_north;
    act _south = &event::move_south;
    act _east = &event::move_east;
    act _west = &event::move_west;
    act _character = &event::character_screen;
    // act _exit = &event::exit;
    act _back = &event::back;
    act _print_map = &event::print_map;
    act _print_inv = &event::print_inventory;
private:
    rng generator;
};
