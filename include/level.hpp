#pragma once

#include <vector>
#include "map.hpp"
#include "character.hpp"

class Level
{
protected:
    Character *player;
    Map *map;

    Textures instpage;
    std::pair<bool, bool> movecamera{};
    std::pair<int, int> cameramovement;
    float camx{}, camy{};

    virtual void loadplayer();
    virtual void loadmap();

    bool finish;

    std::vector<Rectangle> colliders;
    virtual void addcolliders();

    virtual void updatechar(float dt);
    virtual void loadinstr();

public:
    Level();
    ~Level();

    virtual void instr();

    virtual void render();
    virtual void update(float dt);
    virtual bool complete();
};
