#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include <array>

enum class item_rarity { common, uncommon, rare, unique };

class item {
public:
    std::string name;
    item_rarity rarity;

    item();
    virtual ~item();
    std::string set_name(std::string&);
};

class weapon: public item{
public:
    // minimum stats to use weapon:
    // level, strength, dexterity, intelligence
    std::array<long long, 4> min_stats;
    long long level;

    weapon();
    weapon(std::string&, item_rarity&, long long&, std::array<long long, 4>&);
    
    std::string set_name(std::string&, long long&);
    long long set_damage(long long&);
    long long damage;
};

class character {
public:
	character();
    character(std::string);
    std::string name;
    std::vector<item> items;
    std::vector<weapon> weapons;
    weapon equiped_weapon;

    void add_xp(const long long&);
    void mod_hp(const long long&);

    std::unordered_map<std::string, long long&> stats;
    long long str;
    long long dex;
    long long intel;
    long long level;

    long long xPos;
    long long yPos;

    long long damage;
    long long xp;
    long long xp_to_level;
    long long hp;
    long long max_hp;
    long long gold;
};





