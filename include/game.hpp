#pragma once

#include <raylib.h>
#include "character.hpp"

class Game
{
    Character *player;
    Textures map;
    Rectangle mapsrc, mapdest;
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