#pragma once

#include "texture.hpp"

class Map
{
    Textures map;

public:
    Map();
    ~Map();

    Map(const char *path);
    void drawmap();
};
