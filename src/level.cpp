#include "include/level.hpp"

Level::Level() {}

Level::~Level() {}

void Level::loadplayer()
{
    player = new Character("assets/main_char/Idle.png", "assets/main_char/Run.png");
    player->initchar(Vector2{256.f, 256.f}, 0, 1.0 / 15.0, 0.f);
}

void Level::loadmap() {}

void Level::render()
{
    movecamera = player->shouldstay;
    movecamera.first ? cameramovement.first = 1 : cameramovement.first = 0;
    movecamera.second ? cameramovement.second = 1 : cameramovement.second = 0;

    camx = (player->pos.x - 896.f) * cameramovement.first;
    camy = (player->pos.y - 476.f) * cameramovement.second;

    if (!movecamera.first and (player->pos.x > 1000.f))
    {
        camx = 1920.f;
    }
    if (!movecamera.second and (player->pos.y > 1000.f))
    {
        camy = 2760.f;
    }

    map->drawmap(Vector2{camx, camy});
}

void Level::update(float dt)
{
    updatechar(dt);
    for (auto c : colliders)
    {
        player->rec = {player->pos.x + 25.f, player->pos.y + 50.f, 78.f, 72.f};
        if (CheckCollisionRecs(player->rec, c))
        {
            player->pos = player->lastframe;
        }
    }
}

void Level::addcolliders() {}

void Level::loadinstr() {}

void Level::instr() {}

void Level::updatechar(float dt) {}

bool Level::complete() { return false; }
