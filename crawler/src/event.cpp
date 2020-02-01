#include "event.h"

using namespace std;

event::event() : situation{ "welcome to my dungeon crawler v.002", "enter the direction you would like to go" } {}

istream& event::get_selection(istream& ins) {
	selected.clear();
	ins >> selected;
	return ins;
}

void event::make_selection(istream& ins, character& player, map& mp, ostream& outs) {
	if (selected == "north") {
		return move_north(player, mp);
	}
	if (selected == "south") {
		return move_south(player, mp);
	}
	if (selected == "east") {
		return move_east(player, mp);
	}
	if (selected == "west") {
		return move_west(player, mp);
	}
	if (selected == "exit"){
		return;
	}
	else {
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
	outs << endl;
	return outs;
}

ostream& event::print_options(ostream& outs) {
	for (auto& opt : options) {
		outs << opt << "\n";
	}
	outs << "exit\n" <<endl;
	return outs;
}

void event::check_moves(character& chr, map& mp) {
	options.clear();
	if (mp._map[chr.yPos + 1][chr.xPos]) {
		options.push_back("north");
	}
	if (mp._map[chr.yPos - 1][chr.xPos]) {
		options.push_back("south");
	}
	if (mp._map[chr.yPos][chr.xPos + 1]) {
		options.push_back("east");
	}
	if (mp._map[chr.yPos][chr.xPos - 1]) {
		options.push_back("west");
	}
}

void event::move_north(character& chr, map& mp) {
	situation.clear();
	if (mp._map[chr.yPos + 1][chr.xPos]){
		situation.push_back("moved north");
		++chr.yPos;
	}
	else {
		situation.push_back("could not go north");
	}
}
void event::move_south(character& chr, map& mp) {
	situation.clear();
	if (mp._map[chr.yPos - 1][chr.xPos]) {
		situation.push_back("moved south");
		--chr.yPos;
	}
	else {
		situation.push_back("could not go south");
	}
}
void event::move_east(character& chr, map& mp) {
	situation.clear();
	if (mp._map[chr.yPos][chr.xPos + 1]) {
		situation.push_back("moved east");
		++chr.xPos;
	}
	else {
		situation.push_back("could not go east");
	}
}
void event::move_west(character& chr, map& mp) {
	situation.clear();
	if (mp._map[chr.yPos][chr.xPos - 1]) {
		situation.push_back("moved west");
		--chr.xPos;
	}
	else {
		situation.push_back("could not go west");
	}

}