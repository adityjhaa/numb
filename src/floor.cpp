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
    int i = 0;
    for (auto &one_floor : floor)
    {
        one_floor.resize(32);
        for (auto &block : one_floor)
        {
            block.texture.load(path);
            block.rect = {};
            block.is_active = true;
            i++;
            if (i % 3 == 0 || i % 4 == 0)
            {
                block.is_active = false;
            }
        }
    }
}

bool Floor::CheckCollision(Character *player, float playerx, float playery)
{
    Rectangle playerRect = {playerx + 32, playery + 15, 55, 115};
    for (auto &one_floor : floor)
    {
        for (auto &block : one_floor)
        {
            if (block.is_active && (CheckCollisionRecs(playerRect, block.rect)))
            {
                if (playery + 125 > block.rect.y)
                {
                    player->vel.x = 0;
                    if (player->pos.x < block.rect.x)
                        player->pos.x -= 1;
                    else
                        player->pos.x += 1;
                }
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
                block.rect = {static_cast<float>(x - camx), static_cast<float>(y), static_cast<float>(TEXTURE_SIZE), static_cast<float>(TEXTURE_SIZE)};
                Rectangle source{0.0f, 0.0f, static_cast<float>(block.texture.getTexture().height), static_cast<float>(block.texture.getTexture().width)};
                DrawTexturePro(block.texture.getTexture(), source, block.rect, Vector2{}, 0.0, WHITE);
            }
            x += 64;
        }
        y += 1080;
    }
}