#pragma once

#include <raylib.h>
#include "lvl1.hpp"
#include "lvl2.hpp"

class Game
{
    Level1 *lvl1;
    Level2 *lvl2;
    int currLevel;

    bool instruction = true;

public:
    Game();
    ~Game();

    void init(int width, int height, const char *title);

    void startscreen();

    void begin();
    void update(float dt);
    void end();
    void close();
};