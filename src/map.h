#ifndef MAP_H 
#define MAP_H

#include <string>
#include <vector>

class Map 
{
public:
    Map();

    int id = 1;
    int size = 512;
    int seed = 1;
    int ticks = 0;
    int day = 0;
    int day_length = 1800;
    std::string name = "Nexus";
    std::string message = "You have entered the Nexus.";
    std::string gamemode = "adventure";
    std::string difficulty = "normal";
    std::string weather = "clear";
    std::string season = "spring";
    bool hardcore = false;
    bool pvp = false;
    bool spawn_npcs = false;
    bool spawn_monsters = false;
    bool spawn_animals = false;

    static void load_maps(std::vector<Map*> maps);
    static Map* get_map(int id, std::vector<Map*> maps);
};

#endif