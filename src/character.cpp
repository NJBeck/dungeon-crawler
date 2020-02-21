#include "character.h"

using namespace std;
character::character() : name("Character"), str(10), dex(10), intel(10), xPos(0), yPos(0),
                        hp(100), max_hp(100), xp(0), xp_to_level(100), level(1), gold(0) {
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

void character::add_xp(const long long& num){
    auto new_xp = xp + num;
    if (new_xp >= xp_to_level){
        ++level;
        xp = new_xp - xp_to_level;
        xp_to_level = xp_to_level * level * level; //xp to level up goes quadratic with level
        max_hp = max_hp + 10 * (str + dex + intel - 30); //hp increases by 10 for every main stat increase
    }else{
        xp = new_xp;
    }
}


item::item(): name("item"){
    rarity = common;
}

void weapon::set_name(const string& base){
    switch (rarity){
        case common: name = "common level " + to_string(level) + base;
                    break;
        case uncommon: name = "uncommon level " + to_string(level) + base;
                    break;
        case rare: name = "rare level " + to_string(level) + base;
                    break;
        case unique: name = "unique level " + to_string(level) + base;
                    break;
    }
}

weapon::weapon(): level(1) {}

weapon::weapon(item_rarity& rar, long long& lvl){
    rarity = rar;
    level = lvl;
}

sword::sword(): durability(100.0){
    set_name(" sword");
    min_stats[1] = 10 + level - 1;
    damage = (10 + level - 1) * (1 + rarity / 10);
}

