#include <algorithm>
#include "events.h"
#include <memory>

using namespace std;

event::event() : situation{ "welcome to my dungeon crawler v.0.0.6", "enter the option you would like to select" }, screen_width(64) {
}

rng event::generator = rng();

istream& event::get_selection(istream& ins) {
    selected.clear();
    ins >> selected;
    return ins;
}

ostream& event::print_situation(ostream& outs) {
    outs << "\n";
    for (auto& str : situation) {
        outs << str << "\n";
    }
    outs << string(screen_width, '=') << endl;
    return outs;
}

ostream& event::print_options(ostream& outs) {
    for (int i = 0; i < availableOptions.size(); ++i) {
        if (availableOptions[i]) { cout << optToString[i] << endl; }
    }
    return outs;
}

void event::event_loop(istream& ins, ostream& outs){
    get_options();
    print_situation(outs);
    print_options(outs);
    get_selection(ins);
    make_selection();
}

overworld::overworld() : mapRange(16)
{
    strToOpt = {
        {"north", moveNorth},
        {"south", moveSouth},
        {"east", moveEast},
        {"west", moveWest},
        {"inventory", invScreen},
        {"character", chScreen},
        //{"map", mapScreen}
    };

    optToString = {
        {moveNorth, "north"},
        {moveSouth, "south"},
        {moveEast, "east"},
        {moveWest, "west"},
        {invScreen, "inventory"},
        {chScreen, "character"},
        //{mapScreen, "map"},
    };

    availableOptions = vector<bool>(strToOpt.size(), false);

    mp.generatemap();

    player = character("Player");
    player.xPos = mp.map_size / 2;
    player.yPos = mp.map_size / 2;
}


void overworld::make_selection() {
    // check to see if selection is in the possible options
    auto found = strToOpt.find(selected);
    if (found == strToOpt.end() ){
        situation.clear();
        situation.emplace_back("Please make a valid selection");
        event_loop(cin, cout);
    }
    auto selection = found->second;
    // check to see if the option is actually available
    if (!availableOptions[selection]) {
        situation.clear();
        situation.emplace_back("Please make a valid selection");
        event_loop(cin, cout);
    }

    // if it is then we make the appropriate switch
    switch(selection){
        case moveNorth: move_north();
            break;
        case moveSouth: move_south();
            break;
        case moveEast: move_east();
            break;
        case moveWest: move_west();
            break;
        case invScreen: print_inventory();
            break;
        case chScreen: ch_screen();
            break;
        //case mapScreen: print_map();
        //    break;
    }
}

void overworld::get_options() {
    // reset vector of available options to all false
    availableOptions = vector<bool>(strToOpt.size(), false);

    if (mp.cells[player.yPos + 1][player.xPos]) {
        availableOptions[moveNorth] = true;
    }
    if (mp.cells[player.yPos - 1][player.xPos]) {
        availableOptions[moveSouth] = true;
    }
    if (mp.cells[player.yPos][player.xPos + 1]) {
        availableOptions[moveEast] = true;
    }
    if (mp.cells[player.yPos][player.xPos - 1]) {
        availableOptions[moveWest] = true;
    }
    availableOptions[invScreen] = true;
    availableOptions[chScreen] = true;
    //availableOptions[mapScreen] = true;
}

vector<string> overworld::local_map() {
    vector<string> output;

    long long xMin = max(0LL, (player.xPos - (mapRange / 2)));
    long long xMax = min(static_cast<long long>(mp.map_size), player.xPos + (mapRange / 2));
    long long yMin = max(0LL, (player.yPos - (mapRange / 2)));
    long long yMax = min(static_cast<long long>(mp.map_size), player.yPos + (mapRange / 2));


    for (long long i = yMin; i < yMax; ++i) {
        vector<char> temp;
        temp.reserve(2 * mapRange);
        for (long long j = xMin; j < xMax; ++j) {
            if (mp.cells[i][j]) {
                temp.emplace_back('X');
            }
            else {
                temp.emplace_back('|');
            }
            temp.emplace_back(' ');
        }

        output.emplace_back(string(temp.begin(), temp.end()));
    }
    return output;
}

ostream& overworld::print_situation(ostream& outs) {
    // TODO: wrap situations longer than localMap size to screen_width
    vector<string> localMap = local_map();
    int maxLen = screen_width - mapRange - 1;   // the max length a line of situation text can be
    for (int i = 0; i < localMap.size(); ++i) {
        if (i == (situation.size() - 1)){
            situation.emplace_back("");
        }
        if (situation[i].size() > maxLen) {
            // print out the beginning
            outs << situation[i].substr(0, maxLen) + "|" + localMap[i] << endl;
            // chop off the end and add it to the next line 
            situation[i + 1] = situation[i].substr(maxLen) + situation[i + 1];
        }
        else {
            // if the line isn't too long then pad it with spaces
            int diff = maxLen - situation[i].size();
            outs << situation[i] + string(diff, ' ') + "|" + localMap[i] << endl;
        }
    }
    return outs;
}
void overworld::move_north() {
    situation.clear();
    situation.emplace_back(player.name + " moved north");
    ++player.yPos;
    roll_encounter();
}

void overworld::move_south() {
    situation.clear();
    situation.emplace_back(player.name + " moved south");
    --player.yPos;
    roll_encounter();
}

void overworld::move_east() {
    situation.clear();
    situation.emplace_back(player.name + " moved east");
    ++player.xPos;
    roll_encounter();
}

void overworld::move_west() {
    situation.clear();
    situation.emplace_back(player.name + " moved west");
    --player.xPos;
    roll_encounter();
}

void overworld::roll_encounter(double encounter_rate){
    if (encounter_rate > generator.uniform_unit_double()){
        auto enemy = make_unique<character>();
        combat fight(player, *enemy);
        while (fight.selected != "exit" && fight.selected != "continue") {
            fight.event_loop(cin, cout);
        }
        

    }
}

void overworld::ch_screen(){
    CharacterScreen screen(player);
    screen.event_loop(cin, cout);
}

void overworld::print_inventory(){
    InvScreen screen(player);
    screen.event_loop(cin, cout);
}

// definitions for InvScreen class
InvScreen::InvScreen(character& player){
    strToOpt = {{"continue", contin}};
    optToString = { {contin, "continue"} };
    availableOptions = vector<bool>(strToOpt.size(), false);

    situation.clear();
    for (auto& itm : player.items) {
        situation.emplace_back(itm.name);
    }
    for (auto& wep : player.weapons) {
        situation.emplace_back(wep->name);
    }
}

void InvScreen::make_selection(){
    auto found = strToOpt.find(selected);
    if (found == strToOpt.end()) {
        situation.clear();
        situation.emplace_back("Please make a valid selection");
        event_loop(cin, cout);
    }
    auto selection = found->second;

    if (!availableOptions[selection]) {
        situation.clear();
        situation.emplace_back("Please make a valid selection");
        event_loop(cin, cout);
    }

    switch (selection) {
    case 0: cont();
        break;
    }
}

void InvScreen::get_options()
{
    availableOptions = vector<bool>(strToOpt.size(), false);
    availableOptions[contin] = true;
}

// definitions for Character Screen class
CharacterScreen::CharacterScreen(character& player){
    strToOpt = {{"continue", contin}};
    optToString = { {contin, "continue"} };
    availableOptions = vector<bool>(strToOpt.size(), false);

    situation.clear();
    situation.emplace_back("name: " + player.name);
    for (auto& stat : player.stats) {
        situation.emplace_back(stat.first + ": " + to_string(stat.second));
    }
}
void CharacterScreen::get_options() {
    availableOptions = vector<bool>(strToOpt.size(), false);
    availableOptions[contin] = true;
}

void CharacterScreen::make_selection(){
    auto found = strToOpt.find(selected);
    if (found == strToOpt.end()) {
        situation.clear();
        situation.emplace_back("Please make a valid selection");
        event_loop(cin, cout);
    }
    auto selection = found->second;

    if (!availableOptions[selection]) {
        situation.clear();
        situation.emplace_back("Please make a valid selection");
        event_loop(cin, cout);
    }

    switch (selection) {
    case 0: cont();
        break;
    }
}

// class for combat screen
combat::combat(character& plr, character& foe): player(&plr), enemy(&foe) {
    strToOpt = { {"fight", fight},
                 {"exit", ext},
                 {"continue", contin} };
    optToString = { {fight, "fight"},
                    {ext, "exit"},
                    {contin, "continue"} };
    
    situation.clear();
    situation.emplace_back("You have encountered a level " + to_string(foe.level) + " " + foe.name);
}
void combat::make_selection()
{
    auto found = strToOpt.find(selected);
    if (found == strToOpt.end()) {
        situation.clear();
        situation.emplace_back("Please make a valid selection");
        event_loop(cin, cout);
    }
    auto selection = found->second;

    if (!availableOptions[selection]) {
        situation.clear();
        situation.emplace_back("Please make a valid selection");
        event_loop(cin, cout);
    }

    switch (selection) {
    case fight: round();
        break;
    case ext: exit();
        break;
    case contin: cont();
        break;
    }
}

void combat::get_options() {
    availableOptions = vector<bool>(strToOpt.size(), false);

    if (player->hp < 1) {
        availableOptions[ext] = true;
    }
    else
    {
        if (enemy->hp < 1) {
            situation.emplace_back("You have defeated " + enemy->name);
            availableOptions[contin] = true;
        }
        else {
            availableOptions[fight] = true;
        }
    }
}

void combat::receive_damage() {
    player->mod_hp(-1 * enemy->damage);
    situation.emplace_back("You have received " + to_string(enemy->damage) + " damage");
}

void combat::deal_damage() {
    enemy->mod_hp(-1 * player->damage);
    situation.emplace_back("You dealt " + to_string(player->damage) + " damage");
}

void combat::round(){
    situation.clear();

    // case where enemy strikes first
    if (player->dex < enemy->dex) {
        receive_damage();
        if (player->hp > 0) {
            deal_damage();
        }
    }
    else {  // case where player strikes first
        deal_damage();
        if (enemy->hp > 0) {
            receive_damage();
        }
    }
}

void combat::cont(){}

void combat::exit() {}