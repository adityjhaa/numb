#include "include/droppable.hpp"
#define TEXTURE_SIZE 32

char *texturesPath[4] = {(char *)"assets/drops/Instagram.png",
                         (char *)"assets/drops/Twitch.png",
                         (char *)"assets/drops/Twitter.png",
                         (char *)"assets/drops/Youtube.png"};

Droppable::Droppable()
{
    texture;
    incrY = 6.f;
    dropsList;
}

void Droppable::Update()
{
    for (auto &drop : dropsList)
    {
        drop.posY += incrY;
    }
}

void Droppable::Spaw(Character *player, int maxDrops)
{
    if (dropsList.size() < maxDrops)
    {
        int posX = GetRandomValue(player->pos.x - 512.f, player->pos.y + 512.f);
        int posY = static_cast<int>(player->pos.y - 340.f);
        Drop drop;
        drop.posX = posX;
        drop.posY = posY;
        drop.rect;
        dropsList.push_back(drop);
    }
}

void Droppable::Draw(int textureNum, float camx, float camy)
{
    char *path = texturesPath[textureNum];
    texture.load(path);
    for (auto &drop : dropsList)
    {
        Rectangle dest{static_cast<float>(drop.posX - camx), static_cast<float>(drop.posY - camy), static_cast<float>(TEXTURE_SIZE), static_cast<float>(TEXTURE_SIZE)};
        drop.rect = dest;
        Rectangle source{0.0f, 0.0f, static_cast<float>(texture.getTexture().height), static_cast<float>(texture.getTexture().width)};
        DrawTexturePro(texture.getTexture(), source, dest, Vector2{}, 0.0, WHITE);
    }
}

void Droppable::CheckCollisions(Floor *floorObj)
{
    std::vector<std::vector<Block>> floor = floorObj->getFloor();
    for (int j = 0; j < floor.size(); j++)
    {
        for (int k = 0; k < floor[0].size(); k++)
        {
            if (floor[j][k].is_active)
            {
                for (int i = 0; i < dropsList.size(); i++)
                {
                    if (CheckCollisionRecs(floor[j][k].rect, dropsList[i].rect))
                    {
                        floorObj->removeBlock(j, k);
                        dropsList.erase(dropsList.begin() + i);
                    }
                }
            }
        }
    }
}

Droppable::~Droppable()
{
    texture.unload();
}