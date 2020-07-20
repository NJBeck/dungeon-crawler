#include "character.h"
#include "event.h"
#include "map.h"
#include <memory>


using namespace std;

int main() {

        auto world = make_unique<_map>();
        auto main_evt = make_unique<event>();
        world->generatemap();
        auto player = make_unique<character>("Player");
        player->xPos = world->map.size() / 2;
        player->yPos = world->map.size() / 2;
        while (main_evt->selected != "exit"){
                main_evt->check_moves(*player, *world);
                main_evt->event_loop(cout, cin, *player, *world);
        }
        return 0;
}
