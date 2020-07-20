#include "character.h"

using namespace std;

character::character() : name("Character"), str(10), dex(10), intel(10), xPos(0), yPos(0),
                        hp(100), max_hp(100), xp(0), xp_to_level(100), level(1), gold(0) {
    stats = {
        {"level", level},
        {"strength", str},
        {"dexterity", dex},
        {"intelligence",intel},
        {"experience", xp},
        {"experience to level", xp_to_level},
        {"hp", hp},
        {"max hp", max_hp}
    };

    weapons.emplace_back(weapon());
    equiped_weapon = weapons[0];
    damage = str + level + equiped_weapon.damage;

}
character::character(std::string nm): character(){
    name = nm;
}

void character::add_xp(const long long& num){
    auto new_xp = xp + num;
    if (new_xp >= xp_to_level){
        ++level;
        ++str;
        ++dex;
        ++intel;
        xp = new_xp - xp_to_level;
        xp_to_level = xp_to_level * level * level; //xp to level up goes quadratic with level
        max_hp = max_hp + 10 * (str + dex + intel - 30); //hp increases by 10 for every main stat increase
    }else{
        xp = new_xp;
    }
}

void character::mod_hp(const long long& num) {
    hp += num;
    if (hp > max_hp) { hp = max_hp; }
    if (hp < 0) { hp = 0; }
}

item::item(): name("item"){
    rarity = item_rarity::common;
}

item::~item() {};

string item::set_name(string& name){
    switch (rarity){
    default: return "common " + name;
        case item_rarity::common: return "common " + name;
                    
        case item_rarity::uncommon: return "uncommon " + name;
                    
        case item_rarity::rare: return "rare " + name;
                    
        case item_rarity::unique: return "unique " + name;
                    
    }
}



weapon::weapon(): level(1), min_stats{0,0,0,0}{
    string base_name = "fists";
    rarity = item_rarity::common;
    name = set_name(base_name, level);
    damage = set_damage(level);
}

weapon::weapon(string& base_name, item_rarity& rar, long long& lvl, std::array<long long, 4>& min){
    rarity = rar;
    level = lvl;
    min_stats = min;
    name = set_name(base_name, lvl);
    damage = set_damage(lvl);
}

string weapon::set_name(string& name, long long& level) {
    switch (rarity) {
    default: return "common level " + to_string(level) + " " + name;
    case item_rarity::common: return "common level " + to_string(level) + " " + name;
        
    case item_rarity::uncommon: return "uncommon level " + to_string(level) + " " + name;
        
    case item_rarity::rare: return "rare level " + to_string(level) + " " + name;
        
    case item_rarity::unique: return "unique level " + to_string(level) + " " + name;
        
    }
}

long long weapon::set_damage(long long& level) {
    switch (rarity) {
    default: return level;
    case item_rarity::common: return level;
        
    case item_rarity::uncommon: return (long long)(level * 1.25);
        
    case item_rarity::rare: return (long long)(level * 1.5);
        
    case item_rarity::unique: return level * 2;
        
    }
}
//sword::sword(): durability(100.0){
//    set_name(" sword");
//    min_stats[1] = 10 + level - 1;
//    damage = (10 + level - 1) * (1 + rarity / 10);
//}

