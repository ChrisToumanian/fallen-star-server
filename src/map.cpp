#include "map.h"

Map::Map()
{
}

void Map::load_maps(std::vector<Map*>* maps)
{
    Map* map = new Map();
    maps->push_back(map);
}

Map* Map::get_map(int id, std::vector<Map*>* maps)
{
    for (auto& map : *(maps))
    {
        if (map->id == id)
            return map;
    }
    return NULL;
}