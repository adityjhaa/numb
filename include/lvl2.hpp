#pragma once

#include <vector>
#include "map.hpp"
#include "character.hpp"
#include "texture.hpp"

class Level2
{
    Textures *texture;
    Character *player;
    Map *map;


    std::pair<bool, bool> movecamera{};
    std::pair<int, int> cameramovement;
    int droppable_score{};
    float camx{}, camy{};

    void loadplayer();
    void droppables();
    void loadmap();

    std::vector<Rectangle> colliders;
    void addcolliders();

public:
    Level2();
    ~Level2();

    void render();
    void update(float dt);
};