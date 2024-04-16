#include "../include/lvl3.hpp"

Level3::Level3()
{
    loadmap();
    loadplayer();
    addcolliders();
    s = LoadSound("");
}

Level3::~Level3()
{
    player = nullptr;
    map = nullptr;
    UnloadSound(s);
}

void Level3::loadmap()
{
    map = new Map("", 1.f);
}

void Level3::addcolliders()
{
}

void Level3::updatechar(float dt)
{
}

bool Level3::complete()
{
}
