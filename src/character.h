#pragma once
#include <vector>
#include <string>
#include <unordered_map>

class character {
public:
	character();
    character(std::string);
    std::unordered_map<std::string, long long> stats;
    long long str;
    long long dex;
    long long intel;
    long long xPos;
    long long yPos;
	double hp;
	double max_hp;
    long long xp;
    long long xp_to_level;
    std::string name;
    long long level;
};

//class item {
//public:
//    std::string name;
//    enum item_base{
//        sword, bow, wand
//    };
//    enum item_rarity{
//        common, uncommon, rare, unique
//    };
//    unsigned long level;
//    item();
//};



//item::item(): name("item"), level(1){}
