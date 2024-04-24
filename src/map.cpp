#include "include/map.hpp"

Map::Map() {}

Map::~Map()
{
    map.unload();
}

Map::Map(const char *path, float scale)
{
    map.load(path);
    tex = map.getTexture();

    src = {0.f, 0.f, (float)tex.width, (float)tex.height};
    dest = {0.f, 0.f, (float)tex.width * scale, (float)tex.height * scale};
}

void Map::drawmap(Vector2 mappos)
{
    DrawTexturePro(tex, src, dest, mappos, 0.f, WHITE);
}
