#include <algorithm>
#include "event.h"

using namespace std;

event::event() : situation{ "welcome to my dungeon crawler v.0.0.3", "enter the direction you would like to go" } {
    actions["north"] = _north;
    actions["south"] = _south;
    actions["east"] = _east;
    actions["west"] = _west;
    actions["character"] = _character;
    actions["exit"] = _exit;
    actions["back"] = _back;
    actions["map"] = _print_map;
}

istream& event::get_selection(istream& ins) {
    selected.clear();
    ins >> selected;
    return ins;
}

void event::make_selection(istream& ins, character& player, _map& mp, ostream& outs) {
    if (find(options.begin(), options.end(), selected) != options.end()){
        auto& act = actions[selected];
        act(*this, outs, ins, player, mp);
    }
    else{
        outs << "please enter a valid choice" << endl;
        get_selection(ins);
        make_selection(ins, player, mp, outs);
    }
}

ostream& event::print_situation(ostream& outs) {
    outs << "\n";
    for (auto& str : situation) {
        outs << str << "\n";
    }
    outs << string(31, '=') << endl;
    return outs;
}

ostream& event::print_options(ostream& outs) {
    for (auto& opt : options) {
        outs << opt << "\n";
    }
    return outs;
}


void event::check_moves(character& chr, _map& mp) {
    if (mp.map_[chr.yPos + 1][chr.xPos]) {
        options.emplace_back("north");
    }
    if (mp.map_[chr.yPos - 1][chr.xPos]) {
        options.emplace_back("south");
    }
    if (mp.map_[chr.yPos][chr.xPos + 1]) {
        options.emplace_back("east");
    }
    if (mp.map_[chr.yPos][chr.xPos - 1]) {
        options.emplace_back("west");
    }
    options.emplace_back("character");
    options.emplace_back("map");
    options.emplace_back("exit");

}

void event::move_north(ostream& outs, istream& ins, character& chr, _map& mp) {
    situation.clear();
    situation.emplace_back(chr.name + " moved north");
    ++chr.yPos;
}


void event::move_south(ostream& outs, istream& ins, character& chr, _map& mp) {
    situation.clear();
    situation.emplace_back(chr.name + " moved south");
    --chr.yPos;
}

void event::move_east(ostream& outs, istream& ins, character& chr, _map& mp) {
    situation.clear();
    situation.emplace_back(chr.name + " moved east");
    ++chr.xPos;
}

void event::move_west(ostream& outs, istream& ins, character& chr, _map& mp) {
    situation.clear();
    situation.emplace_back(chr.name + " moved west");
    --chr.xPos;
}

void event::character_screen(ostream& outs, istream& ins, character& chr, _map& mp){
    event ch_screen;
    ch_screen.situation.clear();
    for(auto& stat : chr.stats){
        ch_screen.situation.emplace_back(stat.first + ": " + to_string(stat.second));
    }
    ch_screen.options.emplace_back("back");
    ch_screen.print_situation(outs);
    ch_screen.print_options(outs);
    ch_screen.get_selection(ins);
    ch_screen.make_selection(ins, chr, mp, outs);
}

void event::exit(ostream& outs, istream& ins, character& chr, _map& mp){}

void event::back(ostream& outs, istream& ins, character& chr, _map& mp){}

void event::print_map(ostream& outs, istream& ins, character& chr, _map& mp) {
    long long& xPos = chr.xPos;
    long long& yPos = chr.yPos;
    int range = 16;

    long long xMin = max(0LL, (xPos - (range / 2)));
    long long xMax = min(static_cast<long long>(mp.map_.size()), xPos + (range / 2));
    long long yMin = max(0LL, (yPos - (range / 2)));
    long long yMax = min(static_cast<long long>(mp.map_.size()), yPos + (range / 2));

    for (long long i = yMin; i < yMax; ++i){
        for (long long j = xMin; j < xMax; ++j){
            if (mp.map_[i][j]){
                outs << "X ";
            }else{
                outs << "| ";
            }
        }
        outs << endl;
    }
    outs << endl;
}
