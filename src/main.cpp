#include "entities.h"
#include "events.h"
#include "map.h"
#include <memory>


using namespace std;

int main() {
        auto main_evt = make_unique<overworld>();

        while (main_evt->selected != "exit"){
                main_evt->event_loop(cin, cout);
        }
        return 0;
}
