#pragma once

#include <raylib.h>
#include "lvl1.hpp"
#include "lvl2.hpp"
#include "lvl3.hpp"
#include "lvl4.hpp"
#include "home.hpp"
#include "menu.hpp"

class Game
{
    Menu *menu;
    Home *home;
    Level1 *lvl1;
    Level2 *lvl2;
    Level3 *lvl3;
    Level4 *lvl4;
    int currLevel;
    bool mute{}, tut{};

    Textures tutorial;

    bool instruction[4] = {true, true, true, true};

public:
    Game();
    ~Game();

    bool exit{};

    void init(int width, int height, const char *title);

    void startscreen();

    void begin();
    void update(float dt);
    void end();
    void close();
};