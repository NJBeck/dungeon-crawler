#include "character.h"
#include "event.h"
#include "map.h"
#include <memory>


using namespace std;

int main() {

        unique_ptr<_map> world = make_unique<_map>();
        world->generatemap();
        character player = character("Player");
        player.xPos = world->map_.size() / 2;
        player.yPos = world->map_.size() / 2;
        unique_ptr<event> main_evt = make_unique<event>();
        do {
                //evt.generate_situation();
                main_evt->check_moves(player, *world);
                main_evt->print_situation(cout);
                main_evt->print_options(cout);
                main_evt->get_selection(cin);
                main_evt->make_selection(cin, player, *world, cout);
                main_evt->options.clear();
        } while(main_evt->selected != "exit");
        return 0;
}
