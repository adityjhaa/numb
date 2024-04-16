#include "../include/floor.hpp"
#define LEVEL 3
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
    for (auto &one_floor : floor)
    {
        one_floor.resize(32);
        for (auto &block : one_floor)
        {
            block.texture.load(path);
            block.rect = {0.0f, 0.0f, static_cast<float>(TEXTURE_SIZE), static_cast<float>(TEXTURE_SIZE)};
            block.is_active = true;
        }
    }
}

bool Floor::CheckCollision(Character *player)
{
    player->rec = {player->pos.x + 25.f, player->pos.y + 50.f, 78.f, 72.f};
    for (auto &one_floor : floor)
    {
        for (auto &block : one_floor)
        {
            if (block.is_active && CheckCollisionRecs(player->rec, block.rect))
            {
                return true;
            }
        }
    }
    return false;
}

void Floor::Draw(Character *player, float camx, float camy)
{
    int x = 0, y = 1080;
    y -= camy;
    for (auto &one_floor : floor)
    {
        x = 0;
        for (auto &block : one_floor)
        {
            if (block.is_active)
            {
                block.rect = {static_cast<float>(x), static_cast<float>(y), static_cast<float>(TEXTURE_SIZE), static_cast<float>(TEXTURE_SIZE)};
                Rectangle source{0.f - camx, 0.f, static_cast<float>(block.texture.getTexture().width), static_cast<float>(block.texture.getTexture().height)};
                DrawTexturePro(block.texture.getTexture(), source, block.rect, Vector2{}, 0.0, WHITE);
            }
            x += 64;
        }
        y += 1080 + 128;
    }
}