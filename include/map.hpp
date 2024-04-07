#pragma once

#include "texture.hpp"
#include <vector>

class Map
{
    Textures map;
    Texture2D tex;
    float scale{4.f};
    Rectangle src, dest;

public:
    Map();
    ~Map();

    Map(const char *path);
    void drawmap(Vector2 mappos);
};
