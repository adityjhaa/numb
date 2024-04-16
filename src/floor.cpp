#include "../include/floor.hpp"
#define LEVEL 2
#define TEXTURE_SIZE 64

Floor::Floor()
{
    floor = {};
}

Floor::~Floor()
{
}

Floor::Floor(char *path)
{
    floor.resize(LEVEL);
    int x = 0, y = 0;
    for (auto &one_floor : floor)
    {
        x = 0;
        one_floor.resize(32);
        for (auto &block : one_floor)
        {
            block.texture.load(path);
            block.rect = {static_cast<float>(x), static_cast<float>(y), static_cast<float>(TEXTURE_SIZE), static_cast<float>(TEXTURE_SIZE)};
            block.is_active = true;
            x += 64;
        }
        y += 500;
    }
}

void Floor::CheckCollision()
{

}

void Floor::Draw()
{
    for (auto &one_floor : floor)
    {
        for (auto &block : one_floor)
        {
            if (block.is_active)
            {
                Rectangle source{0.f, 0.f, static_cast<float> block.texture.getTexture().width, static_cast<float> block.texture.getTexture().height};
                DrawTexturePro(block.texture.getTexture(), source, block.rect, Vector2{}, 0.0, WHITE);
            }
        }
    }
}