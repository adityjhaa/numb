#pragma once

#include "texture.hpp"
#include "character.hpp"
#include <vector>
#include <iostream>
#define TEXTURE_SIZE 32
#define MAX_DROPS 4

class Droppable
{
    Textures texture;
    float incrY;
    std::vector<std::pair<int, int>> dropsList;

public:
    Droppable();
    void Spaw(Character* player);
    void Update();
    void Draw(int textureNum, float camx, float camy);
    ~Droppable();
};