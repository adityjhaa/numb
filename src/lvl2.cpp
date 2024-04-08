#include "../include/lvl2.hpp"
#include <iostream>

Level2::Level2()
{
    loadplayer();
    loadmap();
}

Level2::~Level2()
{
    player = nullptr;
    map = nullptr;
}

void Level2::loadplayer()
{
    player = new Character("assets/main_char/Idle.png", "assets/main_char/Run.png");
    player->initchar(Vector2{256.f, 256.f}, 0, 1.0 / 15.0, 0.f);
}

void Level2::loadmap()
{
    map = new Map("assets/map2.png");
}

void Level2::render()
{
    movecamera = player->movecamera();
    movecamera.first ? cameramovement.first = 1 : cameramovement.first = 0;
    movecamera.second ? cameramovement.second = 1 : cameramovement.second = 0;

    BeginDrawing();
    ClearBackground(WHITE);

    camx = (player->getpos().x - 896.f) * cameramovement.first;
    camy = (player->getpos().y - 476.f) * cameramovement.second;

    if (!movecamera.first and (player->getpos().x > 1000.f))
    {
        camx = 1920.f;
    }
    if (!movecamera.second and (player->getpos().y > 1000.f))
    {
        camy = 2760.f;
    }

    map->drawmap(Vector2{camx, camy});
}

void Level2::update(float dt)
{
    player->updatechar(dt, 2);
}