#include "character.h"

character::character() : str(10), dex(10), intel(10), xPos(0), yPos(0),
                        hp(100.0), max_hp(100.0), xp(0), xp_to_level(100), name("Character"), level(1) {
    stats["Level"] = level;
    stats["Strength"] = str;
    stats["Dexterity"] = dex;
    stats["Intelligence"] = intel;
    stats["Experience"] = xp;
    stats["Exp to level up"] = xp_to_level;
}
character::character(std::string nm) : character(){
    name = nm;
}
