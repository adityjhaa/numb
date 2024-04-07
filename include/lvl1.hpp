#pragma once

#include "map.hpp"
#include "character.hpp"

class Level1
{
    Character *player;
    Map *map;

    std::pair<bool, bool> movecamera{};
    std::pair<int, int> cameramovement;
    float camx{}, camy{};

    void loadplayer();
    void loadmap();

public:
    Level1();
    ~Level1();

    void render();
    void update(float dt);
};
