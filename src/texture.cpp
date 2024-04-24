#include "include/texture.hpp"

Textures::Textures() {}

void Textures::load(const char *path)
{
    texture = LoadTexture(path);
}

void Textures::unload()
{
    UnloadTexture(texture);
}

Texture2D Textures::getTexture()
{
    return texture;
}
