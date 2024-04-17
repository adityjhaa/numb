#include "../include/droppable.hpp"

char *texturesPath[4] = {(char *)"assets/drops/Instagram.png",
                         (char *)"assets/drops/Twitch.png",
                         (char *)"assets/drops/Twitter.png",
                         (char *)"assets/drops/Youtube.png"};

Droppable::Droppable()
{
    texture;
    incrY = 4.f;
    dropsList;
}

void Droppable::Update()
{
    for (auto &drop : dropsList)
    {
        drop.second += incrY;
    }
}

void Droppable::Spaw(Character *player)
{
    if (dropsList.size() < MAX_DROPS)
    {
        int posX = GetRandomValue(player->pos.x - 512.f, player->pos.y + 512.f);
        int posY = static_cast<int>(player->pos.y - 512.f);
        dropsList.push_back({posX, posY});
    }
}

void Droppable::Draw(int textureNum, float camx, float camy)
{
    char *path = texturesPath[textureNum];
    texture.load(path);
    for (auto &drop : dropsList)
    {
        Rectangle dest{static_cast<float>(drop.first - camx), static_cast<float>(drop.second - camy), static_cast<float>(TEXTURE_SIZE), static_cast<float>(TEXTURE_SIZE)};
        Rectangle source{0.0f, 0.0f, static_cast<float>(texture.getTexture().height), static_cast<float>(texture.getTexture().width)};
        DrawTexturePro(texture.getTexture(), source, dest, Vector2{}, 0.0, WHITE);
    }
}

Droppable::~Droppable()
{
    texture.unload();
}