#include "character.h"
#include "event.h"
#include "map.h"

using namespace std;

int main() {
	map mp(64);
	mp.generatemap();
	character player;
	player.xPos = (int)mp._map.size() / 2;
	player.yPos = (int)mp._map.size() / 2;
	event evt;
	mp.print_map(cout);
	do {
		evt.check_moves(player, mp);
		evt.print_situation(cout);
		evt.print_options(cout);
		evt.get_selection(cin);
		evt.make_selection(cin, player, mp, cout);
	} while(evt.selected != "exit");
	return 0;
}