#include "../include/map.hpp"

Map::Map() {}

Map::~Map()
{
    map.unload();
}

Map::Map(const char *path)
{
    map.load(path);
}

void Map::drawmap()
{
    
}
