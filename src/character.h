#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include <array>

class item {
public:
    std::string name;
    enum item_rarity{
        common, uncommon, rare, unique
    };
    item_rarity rarity;

    item();
};

class weapon: public item{
public:
    // minimum stats to use weapon:
    // level, strength, dexterity, intelligence
    std::array<long long, 4> min_stats;
    long long level;

    void set_name(const std::string&);
    weapon();
    weapon(item_rarity&, long long&);
};

class sword: public weapon{
public:
    long long damage;
    double durability;

    sword();
};


class character {
public:
	character();
    character(std::string);
    std::string name;
    std::vector<item> inventory;

    void add_xp(const long long&);

    std::unordered_map<std::string, long long> stats;
    long long str;
    long long dex;
    long long intel;
    long long level;

    long long xPos;
    long long yPos;

protected:
    long long xp;
    long long xp_to_level;
    long long hp;
    long long max_hp;
    long long gold;

};





