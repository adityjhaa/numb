#pragma once

#include "floor.hpp"
#include <vector>

struct Drop
{
    int posX;
    int posY;
    Rectangle rect;
};

class Droppable
{
    Textures texture;
    float incrY;
    std::vector<Drop> dropsList;

public:
    Droppable();
    void Spaw(Character *player, int multipler);
    void Update();
    void Draw(int textureNum, float camx, float camy);
    void CheckCollisions(Floor *floorObj);
    ~Droppable();
};