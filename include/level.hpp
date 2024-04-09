#pragma once

#include <vector>
#include "map.hpp"
#include "character.hpp"

class Level
{
protected:
    Character *player;
    Map *map;

    std::pair<bool, bool> movecamera{};
    std::pair<int, int> cameramovement;
    float camx{}, camy{};

    void loadplayer();
    virtual void loadmap();

    std::vector<Rectangle> colliders;
    virtual void addcolliders();
    
    virtual void updatechar(float dt);

public:
    Level();
    ~Level();

    virtual void render();
    virtual void update(float dt);
};
