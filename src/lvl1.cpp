#include "../include/lvl1.hpp"
#include <iostream>

Level1::Level1()
{
    loadplayer();
    loadmap();
    addcolliders();
}

Level1::~Level1()
{
    player = nullptr;
    map = nullptr;
}

void Level1::loadplayer()
{
    player = new Character("assets/main_char/Idle.png", "assets/main_char/Run.png");
    player->initchar(Vector2{256.f, 256.f}, 0, 1.0 / 15.0, 0.f);
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
    for (auto c : colliders)
    {
        if (CheckCollisionRecs(player->getrec(), c))
        {
            player->undomove();
        }
    }
}

void Level1::addcolliders()
{
    colliders.push_back(Rectangle{192.f, 192.f, 704.f, 64.f});
    colliders.push_back(Rectangle{192.f, 256.f, 64.f, 1024.f});
    colliders.push_back(Rectangle{832.f, 256.f, 64.f, 384.f});
    colliders.push_back(Rectangle{256.f, 1216.f, 384.f, 64.f});
    colliders.push_back(Rectangle{640.f, 640.f, 2560.f, 64.f});
    colliders.push_back(Rectangle{640.f, 704.f, 64.f, 192.f});
    colliders.push_back(Rectangle{1024.f, 704.f, 64.f, 192.f});
    colliders.push_back(Rectangle{640.f, 1024.f, 64.f, 2176.f});
    colliders.push_back(Rectangle{3136.f, 704.f, 64.f, 2496.f});
    colliders.push_back(Rectangle{704.f, 3136.f, 2112.f, 64.f});
    colliders.push_back(Rectangle{2944.f, 3136.f, 192.f, 64.f});
    colliders.push_back(Rectangle{704.f, 1024.f, 192.f, 64.f});
    colliders.push_back(Rectangle{832.f, 832.f, 64.f, 192.f});
    colliders.push_back(Rectangle{1024.f, 1024.f, 256.f, 64.f});
    colliders.push_back(Rectangle{1216.f, 832.f, 64.f, 192.f});
    colliders.push_back(Rectangle{1280.f, 832.f, 384.f, 64.f});
    colliders.push_back(Rectangle{1792.f, 704.f, 64.f, 192.f});
    colliders.push_back(Rectangle{1600.f, 896.f, 64.f, 448.f});
    colliders.push_back(Rectangle{1664.f, 1024.f, 320.f, 64.f});
    colliders.push_back(Rectangle{1984.f, 832.f, 64.f, 512.f});
    colliders.push_back(Rectangle{2048.f, 832.f, 192.f, 64.f});
    colliders.push_back(Rectangle{2176.f, 896.f, 64.f, 1472.f});
    colliders.push_back(Rectangle{2368.f, 704.f, 64.f, 384.f});
    colliders.push_back(Rectangle{2752.f, 704.f, 64.f, 128.f});
    colliders.push_back(Rectangle{2560.f, 832.f, 448.f, 64.f});
    colliders.push_back(Rectangle{2240.f, 1216.f, 320.f, 64.f});
    colliders.push_back(Rectangle{2560.f, 896.f, 64.f, 768.f});
    colliders.push_back(Rectangle{2944.f, 896.f, 64.f, 1984.f});
    colliders.push_back(Rectangle{2944.f, 3008.f, 64.f, 128.f});
    colliders.push_back(Rectangle{3200.f, 3008.f, 384.f, 64.f});
    colliders.push_back(Rectangle{2688.f, 3200.f, 64.f, 384.f});
    colliders.push_back(Rectangle{3584.f, 3008.f, 64.f, 640.f});
    colliders.push_back(Rectangle{2688.f, 3584.f, 896.f, 64.f});
    colliders.push_back(Rectangle{832.f, 1216.f, 448.f, 64.f});
    colliders.push_back(Rectangle{832.f, 1280.f, 64.f, 448.f});
    colliders.push_back(Rectangle{1216.f, 1280.f, 64.f, 448.f});
    colliders.push_back(Rectangle{1408.f, 1024.f, 64.f, 512.f});
    colliders.push_back(Rectangle{1024.f, 1408.f, 64.f, 448.f});
    colliders.push_back(Rectangle{704.f, 1856.f, 576.f, 64.f});
    colliders.push_back(Rectangle{1280.f, 1664.f, 192.f, 64.f});
    colliders.push_back(Rectangle{832.f, 1920.f, 64.f, 576.f});
    colliders.push_back(Rectangle{896.f, 2240.f, 384.f, 64.f});
    colliders.push_back(Rectangle{896.f, 2432.f, 192.f, 64.f});
    colliders.push_back(Rectangle{704.f, 2624.f, 192.f, 64.f});
    colliders.push_back(Rectangle{1472.f, 1472.f, 576.f, 64.f});
    colliders.push_back(Rectangle{1792.f, 1216.f, 64.f, 256.f});
    colliders.push_back(Rectangle{1600.f, 1536.f, 64.f, 256.f});
    colliders.push_back(Rectangle{1024.f, 2048.f, 384.f, 64.f});
    colliders.push_back(Rectangle{1408.f, 1728.f, 64.f, 768.f});
    colliders.push_back(Rectangle{1600.f, 1536.f, 64.f, 256.f});
    colliders.push_back(Rectangle{1792.f, 1664.f, 64.f, 640.f});
    colliders.push_back(Rectangle{1984.f, 1536.f, 64.f, 576.f});
    colliders.push_back(Rectangle{1856.f, 2048.f, 128.f, 64.f});
    colliders.push_back(Rectangle{1856.f, 2240.f, 192.f, 64.f});
    colliders.push_back(Rectangle{2368.f, 1408.f, 64.f, 384.f});
    colliders.push_back(Rectangle{1472.f, 1920.f, 320.f, 64.f});
    colliders.push_back(Rectangle{2368.f, 1792.f, 384.f, 64.f});
    colliders.push_back(Rectangle{2752.f, 1024.f, 64.f, 1216.f});
    colliders.push_back(Rectangle{2816.f, 1216.f, 128.f, 64.f});
    colliders.push_back(Rectangle{2240.f, 1984.f, 384.f, 64.f});
    colliders.push_back(Rectangle{1600.f, 2112.f, 64.f, 512.f});
    colliders.push_back(Rectangle{1664.f, 2432.f, 192.f, 64.f});
    colliders.push_back(Rectangle{1216.f, 2432.f, 192.f, 64.f});
    colliders.push_back(Rectangle{1280.f, 2432.f, 192.f, 64.f});
    colliders.push_back(Rectangle{1024.f, 2496.f, 64.f, 320.f});
    colliders.push_back(Rectangle{1216.f, 2496.f, 64.f, 512.f});
    colliders.push_back(Rectangle{832.f, 2816.f, 256.f, 64.f});
    colliders.push_back(Rectangle{832.f, 2880.f, 64.f, 128.f});
    colliders.push_back(Rectangle{1024.f, 3008.f, 64.f, 128.f});
    colliders.push_back(Rectangle{1408.f, 2624.f, 448.f, 64.f});
    colliders.push_back(Rectangle{1408.f, 2688.f, 64.f, 320.f});
    colliders.push_back(Rectangle{1600.f, 2816.f, 64.f, 320.f});
    colliders.push_back(Rectangle{1792.f, 2688.f, 64.f, 448.f});
    colliders.push_back(Rectangle{1984.f, 2304.f, 64.f, 704.f});
    colliders.push_back(Rectangle{2048.f, 2496.f, 128.f, 64.f});
    colliders.push_back(Rectangle{2176.f, 2496.f, 64.f, 128.f});
    colliders.push_back(Rectangle{2176.f, 2624.f, 256.f, 64.f});
    colliders.push_back(Rectangle{2176.f, 2880.f, 64.f, 256.f});
    colliders.push_back(Rectangle{2368.f, 2688.f, 64.f, 256.f});
    colliders.push_back(Rectangle{2368.f, 2944.f, 256.f, 64.f});
    colliders.push_back(Rectangle{2432.f, 2176.f, 320.f, 64.f});
    colliders.push_back(Rectangle{2368.f, 2176.f, 64.f, 320.f});
    colliders.push_back(Rectangle{2560.f, 2368.f, 256.f, 64.f});
    colliders.push_back(Rectangle{2560.f, 2432.f, 64.f, 512.f});
    colliders.push_back(Rectangle{2624.f, 2560.f, 320.f, 64.f});
    colliders.push_back(Rectangle{2752.f, 2752.f, 64.f, 384.f});
}
