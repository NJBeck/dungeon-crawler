#pragma once
#include <string>
#include "character.h"
#include "map.h"
#include <unordered_map>
#include <unordered_set>
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
	std::unordered_set<std::string> options;
	std::string selected;
    std::vector<character> characters;
    std::unordered_map<std::string, int> possibleOptions;

	std::istream& get_selection(std::istream&);
    virtual void make_selection();
	std::ostream& print_situation(std::ostream&);
	std::ostream& print_options(std::ostream&);

    void roll_encounter(character&, _map&, double = .5);
    void encounter(character&, character&, _map&);
    void event_loop(std::ostream&, std::istream&, character&, _map&);
    void receive_damage(character&, character&);
    void deal_damage(character&, character&);

private:
    // the actions available to characters

    void exit(std::ostream&, std::istream&, character&, _map&);

    void fight(std::ostream&, std::istream&, character&, _map&);
    void cont(std::ostream&, std::istream&, character&, _map&);

    
    rng generator;
};

class overworld : private event{
    overworld();


    void make_selection();
    void move_north();
    void move_south();
    void move_east();
    void move_west();
    void character_screen();
    std::vector<std::string> local_map(int);
    void print_inventory();
    void check_moves();

private:
    _map mp;
    character player

};