#include "../include/lvl1.hpp"
#include <iostream>

Level1::Level1()
{
    loadplayer();
    loadmap();
}

Level1::~Level1()
{
    player = nullptr;
    map = nullptr;
}


void Level1::loadplayer()
{
    player = new Character("assets/main_char/Idle.png", "assets/main_char/Run.png");
    player->initchar(Vector2{250.f, 250.f}, 0, 1.0 / 15.0, 0.f);
}

void Level1::loadmap()
{
    map = new Map("assets/map.png");
}

void Level1::render()
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

void Level1::update(float dt)
{
    player->updatechar(dt);
}
