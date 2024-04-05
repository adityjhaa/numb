#pragma once

#include <raylib.h>
#include "character.hpp"
#include <iostream>

class Game
{
    void draw(float dt);
    Character *m;

public:
    Game();
    ~Game();

    void initwindow(int width, int height, const char *title);

    void startscreen(const char *name);

    void addCharacter();

    void render(float dt);
};