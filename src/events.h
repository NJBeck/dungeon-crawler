#pragma once
#include <string>
#include "entities.h"
#include "map.h"
#include <unordered_map>
#include <unordered_set>
#include "rng.h"
#include <vector>

class event {
public:
	event();
    /*
     * class that handles all the actions and events taken
     * at every loop the situation is printed at the top of the screen
     * and options are printed at the bottom
     * a selection is taken and switched on using a hash map
    */
    std::vector<std::string> situation;         // description of scenario
    std::string selected;                       // option selected by user

    // using 2 hash maps to create a bijection between the strings of the options and ints
    // the ints are used in the switch to make the selection and to order the output of options
    std::unordered_map<std::string, int> strToOpt;
    std::unordered_map<int, std::string> optToString;
    std::vector<bool> availableOptions;         // position and value of bool indicates the options available
    int screen_width;

    // the game loop functions
    virtual void get_options() = 0;
	virtual std::ostream& print_situation(std::ostream&);
	std::ostream& print_options(std::ostream&);
    std::istream& get_selection(std::istream&);
    virtual void make_selection() = 0;
    void event_loop(std::istream&, std::ostream&);
 
    static rng generator;
};

class overworld : public event{
public:
    // the event class handling movement around the main game world
    overworld();

    virtual void make_selection();
    virtual void get_options();
    std::ostream& print_situation(std::ostream&) override;


private:
    // enum of the options will be the ints that strToOpt maps to and optToString maps from
    enum option{moveNorth, moveSouth, moveEast, moveWest, chScreen, invScreen};

    void roll_encounter(double = .5);
    std::vector<std::string> local_map();

    // the potential options available in a overworld screen
    void move_north();
    void move_south();
    void move_east();
    void move_west();
    void ch_screen();
    void print_inventory();

    map mp;
    character player;
    int mapRange;
};

class CharacterScreen : public event{
public:
    CharacterScreen(character&);
    void cont() {};
    enum option{contin};
    virtual void make_selection();
    virtual void get_options();
};

class InvScreen : public event{
public:
    InvScreen(character&);
    void cont() {};
    enum option{contin};
    virtual void make_selection();
    virtual void get_options();
};

class combat : public event {
public:
    combat(character&, character&);
private:
    character* player;
    character* enemy;
    enum option{fight, ext, contin};

    virtual void make_selection();
    virtual void get_options();

    void round();
    void cont();
    void exit();

    void receive_damage();
    void deal_damage();
};