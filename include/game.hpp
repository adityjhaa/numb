#pragma once

#include <raylib.h>
#include "character.hpp"
#include "map.hpp"

class Game
{
    Character *player;
    Map *map;

    std::pair<bool, bool> movecamera{};
    std::pair<int, int> cameramovement;
    float camx{}, camy{};

    void loadplayer();
    void loadmap();

public:
    Game();
    ~Game();

    void init(int width, int height, const char *title);

    void startscreen(const char *name);

    void render();
    void update(float dt);
    void end();
    void close();
};