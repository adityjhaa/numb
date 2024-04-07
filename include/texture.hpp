#pragma once

#include <raylib.h>

class Textures
{
    Texture2D texture;

public:
    Textures();

    void load(const char *path);

    void unload();

    Texture2D getTexture();
};