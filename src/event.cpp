#include <algorithm>
#include "event.h"
#include <memory>

using namespace std;

event::event() : situation{ "welcome to my dungeon crawler v.0.0.5", "enter the direction you would like to go" } {
}

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
    if (mp.map[chr.yPos + 1][chr.xPos]) {
        options.emplace_back("north");
    }
    if (mp.map[chr.yPos - 1][chr.xPos]) {
        options.emplace_back("south");
    }
    if (mp.map[chr.yPos][chr.xPos + 1]) {
        options.emplace_back("east");
    }
    if (mp.map[chr.yPos][chr.xPos - 1]) {
        options.emplace_back("west");
    }
    options.emplace_back("character");
    options.emplace_back("map");
    options.emplace_back("inventory");
}

void event::move_north(ostream& outs, istream& ins, character& chr, _map& mp) {
    situation.clear();
    situation.emplace_back(chr.name + " moved north");
    ++chr.yPos;
    roll_encounter(chr, mp);
}

void event::move_south(ostream& outs, istream& ins, character& chr, _map& mp) {
    situation.clear();
    situation.emplace_back(chr.name + " moved south");
    --chr.yPos;
    roll_encounter(chr, mp);
}

void event::move_east(ostream& outs, istream& ins, character& chr, _map& mp) {
    situation.clear();
    situation.emplace_back(chr.name + " moved east");
    ++chr.xPos;
    roll_encounter(chr, mp);
}

void event::move_west(ostream& outs, istream& ins, character& chr, _map& mp) {
    situation.clear();
    situation.emplace_back(chr.name + " moved west");
    --chr.xPos;
    roll_encounter(chr, mp);
}

void event::character_screen(ostream& outs, istream& ins, character& chr, _map& mp){
    event ch_screen;
    ch_screen.situation.clear();
    for(auto& stat : chr.stats){
        ch_screen.situation.emplace_back(stat.first + ": " + to_string(stat.second));
    }
    ch_screen.options.emplace_back("continue");
    ch_screen.event_loop(outs, ins, chr, mp);
}

void event::print_inventory(std::ostream& outs, std::istream& ins, character& chr, _map& mp){
    event inv_screen;
    inv_screen.situation.clear();
    for (auto& itm : chr.items) {
        inv_screen.situation.emplace_back(itm.name);
    }
    for (auto& wep : chr.weapons) {
        inv_screen.situation.emplace_back(wep.name);
    }
    inv_screen.options.emplace_back("continue");
    inv_screen.event_loop(outs, ins, chr, mp);
}



void event::roll_encounter(character & chr, _map& mp, double encounter_rate){
    if (encounter_rate > generator.uniform_unit_double()){
        auto enemy = character("Enemy");
        enemy.level = chr.level;
        encounter(chr, enemy, mp);
    }
}

void event::encounter(character& chr, character& enmy, _map& mp) {
    auto encounter = make_unique<event>(event());
    encounter->situation.clear();
    encounter->characters.emplace_back(enmy);
    encounter->situation.emplace_back("You have encountered: ");
    encounter->situation.emplace_back("level " + to_string(enmy.level) + " " + enmy.name);
    encounter->options.emplace_back("fight");
    encounter->event_loop(cout, cin, chr, mp);
}
void event::receive_damage(character& player, character& enmy) {
    player.mod_hp(-1 * enmy.damage);
    situation.emplace_back("You have received " + to_string(enmy.damage) + " damage");
}

void event::deal_damage(character& player, character& enmy) {
    enmy.mod_hp(-1 * player.damage);
    situation.emplace_back("You dealt " + to_string(player.damage) + " damage");
}

void event::fight(ostream& outs, istream& ins, character& chr, _map& mp){
    situation.clear();
    character& enmy = characters[0];
    if (chr.dex < enmy.dex) {
        receive_damage(chr, enmy);
        if (chr.hp > 0) {
            deal_damage(chr, enmy);
        }
    }
    else {
        deal_damage(chr, enmy);
        if (enmy.hp > 0) {
            receive_damage(chr, enmy);
        }
    }

    if (chr.hp > 0) {
        if (enmy.hp > 0) {
            options.emplace_back("fight");
        }
        else {
            situation.emplace_back(enmy.name + " has been slain");
            auto level_before = chr.level;
            chr.add_xp(enmy.level * enmy.max_hp);
            if (level_before != chr.level) {
                situation.emplace_back(chr.name + " has leveled up");
            }
            options.emplace_back("continue");
        }
    }
    else {
        situation.emplace_back("You have died");
        options.emplace_back("exit");
    }
    event_loop(cout, cin, chr, mp);
}

void event::event_loop(){
    print_situation(outs);
    print_options(outs);
    get_selection(ins);
    make_selection();
}

void event::exit(ostream& outs, istream& ins, character& chr, _map& mp){}
void event::cont(std::ostream&, std::istream&, character&, _map&) {};

overworld::overworld(){
    possibleOptions = {
            {"north", 0},
            {"south", 1},
            {"east", 2},
            {"west", 3},
    };
}

void overworld::make_selection() {
    auto found = options.find(selected);
    if (found != options.end()){
        switch(*found){
            case 0: move_north();
                break;
            case 1: move_south();
                break;
            case 2: move_east();
                break;
            case 3: move_west();
                break;
        }
    }
    else{
        situation.emplace_back("Please make a valid selection");
        event_loop();
    }
}

vector<string> overworld::local_map(int range) {
    vector<string> output;

    long long xMin = max(0LL, (player.xPos - (range / 2)));
    long long xMax = min(static_cast<long long>(mp.map.size()), player.xPos + (range / 2));
    long long yMin = max(0LL, (player.yPos - (range / 2)));
    long long yMax = min(static_cast<long long>(mp.map.size()), player.yPos + (range / 2));


    for (long long i = yMin; i < yMax; ++i){
        char temp[range];
        for (long long j = xMin; j < xMax; ++j){
            if (mp.map[i][j]){
                temp[j] = 'O';
            }else{
                temp[j] = 'X';
            }
        }
        output.emplace_back(string(temp));
    }
    return output;
}