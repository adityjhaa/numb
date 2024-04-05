#pragma once

#include <raylib.h>

class Game
{
    void draw();

public:
    Game();
    ~Game();

    void initwindow(int width, int height, const char *title);

    void render();
};