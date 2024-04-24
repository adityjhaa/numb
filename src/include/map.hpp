#pragma once

#include "texture.hpp"

class Map
{
    Textures map;
    Texture2D tex;
    Rectangle src, dest;

public:
    Map();
    ~Map();

    Map(const char *path, float scale);
    void drawmap(Vector2 mappos);
};
